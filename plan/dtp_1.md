# 数据传输协议（DTP） 0.1

该协议负责将上层数据可靠地从主机传输至虚拟机。为此使用的手段有：封装数据包、内容校验、超时检测、自动重传。

## 格式&含义

### 主机→虚拟机

主机通过模拟键盘输入向虚拟机发送数据，数据的发送是以**包**为单位的，包个格式如下：

```
<ABCDxxxx>
```

其中：

- <code>&lt;</code>和<code>&gt;</code>是包的分界符，标志包的开头和结尾。中间是包内容。
- <code>ABCD</code>是四位十六进制数校验码。
- <code>xxxx</code>是上层数据。

注释：

- 接收程序准备使用C#编写，打算用C#对字符串的<code>hashCode()</code>函数，对校验码之后、结尾符之前的字符串产生校验值。取该校验值十六进制表示中的四位作为校验码。
- 要求上层数据不含大小于号字符。（并不保证数据的透明传输。）

### 虚拟机→主机

![](recv_1.png)

接收程序是全屏显示的，它占用屏幕四角，显示带颜色的方块，以此向主机发送消息。初始状态下四个方块置黑。我们只使用左上角和右上角的方块。

左上角方块：

- 表示当前是否“忙”，也就是在最近500ms内，是否有按键输入。
- 蓝色表示忙
- 黑色表示空闲

右上角方块：

- 表示当前的接收结果。
- 蓝色表示就绪。
- 黄色表示已经开始接收，但还未接收完。
- 红色表示接收出错，包括：还就绪，中途超时、校验错误。
- 绿色表示接收成功。

## 状态转换规则

### 接收方

接收方有2个状态机。

状态机1负责**忙检测**，也用于**超时检测**。它有两个状态：

```
State 1: （初始状态）
	有按键输入→设置状态为【忙】，跳到 State 2
    200ms后→重置结果为【就绪】

State 2:
	200ms后→设置状态为【空闲】，跳到 State 1
        如果启用了超时检测，那么执行超时后果
    有按键输入→重置定时器，保持本状态
```

状态机2负责接收结果的显示：

```
State 1: （初始状态）
	'<'键按下→设置结果为【已经开始接收】，开启超时检测，跳到 State 2
    其他键按下→设置结果为【接收出错】，保持本状态

State 2:
    超时（状态由【忙】变为【空闲】）→设置结果为【接收出错】，跳到 State 1
    '>'键按下→关闭超时检测，检查包内容，跳到 State 1
    	正确→设置结果为【接收成功】，完成相应动作
        错误→设置结果为【接收出错】
    其他键按下→收集此字符
```

注意：上面没有考虑Esc键。在【空闲】状态下按Esc键，应退出程序。

（**考虑到的问题**：客户端显示红色，我们不知道是上次传输出错&这次传输还未能成功开始，还是这次传输的错误。而一旦检测到红色，就会导致重传。因此加入_自动重置状态_的设计。）

（举例：传送完开始符后，到了传送第2个字符的时候，可能这时虚拟机还没收到开始符，如果不引入自动重置+等待的设计，若上次结果为【接收出错】，就会被当做此次传输的问题。）

（接收方状态变为【空闲】后，要200ms才会重置状态，发送方检测到这一变化最多消耗发送方定时器的周期时间，这一时间要小于200ms，因此能够在状态被重置前读取到它。）

（**应该这样考虑！**一旦出现超时，还有后续数据再传入的可能性非常低。）

### 发送方

发送方在发送数据前，先把封装好的数据包写到缓冲区。整个发送过程就是把缓冲区的内容刷入虚拟机的过程，但在此之前，先等待接收结果变为【就绪】。

发送过程中的状态触发由一个定时器处理，每次定时器超时，就进行一次状态转移。

```
State 2: （初始状态）
    对方结果为【就绪】→进入 State 3
    否则：继续等待

State 3:
    对方结果为【接收出错】→进入 State 4
    缓冲区有字符发送→取出此字符，发送，保持此状态
    缓冲区为空→进入 State 4

State 4:
    对方状态为【忙】→继续等待
    对方状态为【空闲】
      and 对方结果为【接收成功】→调用callback，取下一段数据
      and 对方结果为其他→进行重传
```