
mqttx conn -h '192.168.1.89' -p 1883 -u 'test1' -P 'test1'


### 订阅
mqttx sub -t 'topic/gps' -h '192.168.1.89' -p 1883 -u 'test1' -P 'test1'


# 发布单个消息
mqttx pub -t 'topic/test' -h '192.168.1.89' -p 1883 -m '来自MQTTX CLI的消息' -u 'test1' -P 'test1'

# 发布多个消息（多行）
mqttx pub -t 'hello' -h '192.168.1.89' -p 1883 -s -M

# Connect Benchmark
mqttx bench conn -c 5000

# Subscribe Benchmark
mqttx bench sub -c 5000 -t bench/%i

# Publish Benchmark
mqttx bench pub -c 5000 -t bench/%i

# 指定一个本地内置的场景并开始模拟
mqttx simulate -sc tesla -c 10

# 指定一个场景文件并开始模拟
mqttx simulate -f <scenario file path> -c 10

# 列出内置模拟数据的场景
mqttx ls -sc