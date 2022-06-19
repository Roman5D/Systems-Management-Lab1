# Управление роботехническмии системами.
# Лабораторная работа №1. Кочурин Р.П.
## Терминал 1:
```
catkin_make
roscore
```
## Терминал 2:
```
source devel/setup.bash
rosrun client_server client_server
```
## Терминал 3 (просмотр топика):
```
source devel/setup.bash
rostopic echo topic_parity

```
## Терминал 4:
```
source devel/setup.bash
rosservice call /calc_roots_server "{a: 1, b: 2, c: -3}"
```
