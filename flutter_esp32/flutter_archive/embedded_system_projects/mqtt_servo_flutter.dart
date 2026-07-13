import 'package:flutter/material.dart';
import 'package:google_fonts/google_fonts.dart';
import 'package:mqtt_client/mqtt_client.dart';
import 'package:mqtt_client/mqtt_server_client.dart';

void main() {
  runApp(
    const MaterialApp(
      debugShowCheckedModeBanner: false,
      home: ServoPage(),
    ),
  );
}

class ServoPage extends StatefulWidget {
  const ServoPage({super.key});

  @override
  State<ServoPage> createState() => _ServoPageState();
}

class _ServoPageState extends State<ServoPage> {
  late MqttServerClient client;

  double angle = 90;
  bool connected = false;

  @override
  void initState() {
    super.initState();
    connectMQTT();
  }

  Future<void> connectMQTT() async {
    client = MqttServerClient(
      'broker.hivemq.com',
      'flutter_servo_${DateTime.now().millisecondsSinceEpoch}',
    );

    client.port = 1883;
    client.keepAlivePeriod = 20;
    client.logging(on: true);

    client.onConnected = () {
      print("MQTT Connected");

      setState(() {
        connected = true;
      });
    };

    client.onDisconnected = () {
      print("MQTT Disconnected");

      setState(() {
        connected = false;
      });
    };

    client.onSubscribed = (topic) {
      print("Subscribed to $topic");
    };

    final connMessage = MqttConnectMessage()
        .withClientIdentifier(
          'flutter_servo_${DateTime.now().millisecondsSinceEpoch}',
        )
        .startClean();

    client.connectionMessage = connMessage;

    try {
      await client.connect();
    } catch (e) {
      print("Connection failed: $e");
      client.disconnect();
    }
  }

  void publish(String topic, String message) {
    if (client.connectionStatus?.state != MqttConnectionState.connected) {
      print("MQTT is not connected");
      return;
    }

    final builder = MqttClientPayloadBuilder();
    builder.addString(message);

    client.publishMessage(
      topic,
      MqttQos.atLeastOnce,
      builder.payload!,
    );

    print("Published [$topic] : $message");
  }

  @override
  void dispose() {
    client.disconnect();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(
          "ESP32 Servo Control",
          style: GoogleFonts.jetBrainsMono(
            color: Colors.black,
          ),
        ),
        centerTitle: true,
        backgroundColor: const Color.fromARGB(255, 3, 244, 172),
      ),
      body: Padding(
        padding: const EdgeInsets.all(40),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.stretch,
          children: [
            Text(
              connected ? "MQTT Connected" : "MQTT Disconnected",
              textAlign: TextAlign.center,
              style: TextStyle(
                fontSize: 18,
                color: connected ? Colors.green : Colors.red,
                fontWeight: FontWeight.bold,
              ),
            ),

            const SizedBox(height: 30),

            Text(
              "${angle.toInt()}°",
              textAlign: TextAlign.center,
              style: const TextStyle(
                fontSize: 40,
                fontWeight: FontWeight.bold,
              ),
            ),

            const SizedBox(height: 20),

            Slider(
              min: 0,
              max: 180,
              divisions: 180,
              value: angle,
              label: angle.toInt().toString(),

              onChanged: (value) {
                setState(() {
                  angle = value;
                });
              },

              onChangeEnd: (value) {
                publish(
                  "esp32/servo/angle",
                  value.toInt().toString(),
                );
              },
            ),

            const SizedBox(height: 40),

            Row(
              mainAxisAlignment: MainAxisAlignment.spaceEvenly,
              children: [
                ElevatedButton(
                  onPressed: () {
                    publish("esp32/led/state", "ON");
                  },
                  style: ElevatedButton.styleFrom(
                    backgroundColor: Colors.lightGreenAccent
                  ),
                  child: Text(
                    "LED ON",
                    style: GoogleFonts.jetBrainsMono(
                      color: Colors.black,
                      fontWeight: FontWeight.bold,
                    ),
                  ),
                  
                ),

                ElevatedButton(
                  onPressed: () {
                    publish("esp32/led/state", "OFF");
                  },
                  style: ElevatedButton.styleFrom(
                    backgroundColor: Colors.redAccent,
                  ),
                  child: Text(
                    "LED OFF",
                    style: GoogleFonts.jetBrainsMono(
                      color: Colors.black,
                      fontWeight: FontWeight.bold,
                    ),
                  ),
                ),
              ],
            ),

            const SizedBox(height: 20,),

            Row(
              mainAxisAlignment: MainAxisAlignment.spaceEvenly,
              children: [
                ElevatedButton(
                  onPressed: () {
                    publish("esp32/buzzer/state", "ON");
                  },
                  style: ElevatedButton.styleFrom(
                    backgroundColor: Colors.lightGreenAccent,
                  ),
                  child: Text(
                    "BUZZER ON",
                    style: GoogleFonts.jetBrainsMono(
                      color: Colors.black,
                      fontWeight: FontWeight.bold
                    ),
                  ),
                ),

                ElevatedButton(
                  onPressed:() {
                    publish("esp32/buzzer/state", "OFF");
                  },
                  style: ElevatedButton.styleFrom(
                    backgroundColor: Colors.redAccent,
                  ),
                  child: Text(
                    "BUZZER OFF",
                    style: GoogleFonts.jetBrainsMono(
                      color: Colors.black,
                      fontWeight: FontWeight.bold,
                    ),
                  ),
                ),
              ],
            )
          ],
        ),
      ),
    );
  }
}