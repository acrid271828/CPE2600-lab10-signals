## Repo for Lab Week 10

### Signal Handler

```bash
make handler
./handler
```

Continues on SIGINT (ctrl+c)

### Signal Alarm

```bash
make alarm
./alarm
```

Sets an alarm for 5 seconds where it will terminate

### Signal Segfault

```bash
make segfault
./segfault
```

Doens't terminate on segfaults, so prints in an infinite loop

### Sigaction

```bash
make sigaction
./sigaction
```

Prints the pid of the sending process when recieving SIGUSR1

### Signal Send/Receive

```bash
make send_signal
make recv_signal
./recv_signal
```
In another terminal, with the pid of `./recv_signal`:
```bash
./send_signal <pid>
```

Sends data inside the sigaction

### Signal Tennis

```bash
make tennis_player
./tennis_player
```
In another terminal:
```bash
./tennis_player
```

Enter the pid of one player into the other, and they will play a game of tennis with signals