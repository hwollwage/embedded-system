import 'package:flutter/material.dart';
import 'package:speech_to_text/speech_to_text.dart';
import 'package:mqtt_client/mqtt_client.dart';
import 'package:mqtt_client/mqtt_server_client.dart';

class HomePage extends StatefulWidget {
  const HomePage({super.key});

  @override
  State<HomePage> createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  late MqttServerClient client;
  final SpeechToText speech = SpeechToText();

  bool isListening = false;
  bool mqttConnected = false;

  String spokenText = "";

  @override
  void initState() {
    super.initState();
    initSpeech();
    connectMQTT();
  }

  @override
  void dispose() {
    client.disconnect();
    speech.stop();
    super.dispose();
  }

  Future<void> initSpeech() async {
    bool available = await speech.initialize(
      onStatus: (status) {
        debugPrint("Speech Status : $status");
      },
      onError: (error) {
        debugPrint("Speech Error : $error");
      },
    );

    debugPrint("Speech available : $available");
  }

  Future<void> startListening() async {
    if (!speech.isAvailable) return;

    setState(() {
      isListening = true;
      spokenText = "";
    });

    await speech.listen(
      listenMode: ListenMode.confirmation,
      onResult: (result) {
        setState(() {
          spokenText = result.recognizedWords;
        });

        if (result.finalResult) {
          handleCommand(spokenText);
          stopListening();
        }
      },
    );
  }

  Future<void> stopListening() async {
    await speech.stop();

    setState(() {
      isListening = false;
    });
  }

  void handleCommand(String text) {
    text = text.toLowerCase();

    debugPrint("Recognized: $text");

    // Find the first number in the sentence
    final match = RegExp(r'\d+').firstMatch(text);

    if (match != null) {
      int angle = int.parse(match.group(0)!);

      // Keep angle between 0 and 180
      angle = angle.clamp(0, 180);

      publishServo(angle);

      debugPrint("Servo -> $angle°");
      return;
    }

    // Fallback commands
    if (text.contains("left")) {
      publishServo(0);
    } else if (text.contains("center") || text.contains("middle")) {
      publishServo(90);
    } else if (text.contains("right")) {
      publishServo(180);
    } else {
      debugPrint("Unknown command");
    }
  }

  void publishServo(int angle) {
    if (!mqttConnected) {
      debugPrint("MQTT not connected");
      return;
    }

    final builder = MqttClientPayloadBuilder();
    builder.addString(angle.toString());

    client.publishMessage("servo/angle", MqttQos.atLeastOnce, builder.payload!);

    debugPrint("Published angle : $angle");
  }

  Future<void> connectMQTT() async {
    client = MqttServerClient(
      "broker.hivemq.com",
      "flutter_${DateTime.now().millisecondsSinceEpoch}",
    );

    client.port = 1883;
    client.keepAlivePeriod = 20;
    client.autoReconnect = true;
    client.logging(on: true);

    client.connectionMessage = MqttConnectMessage()
        .withClientIdentifier(client.clientIdentifier!)
        .startClean();

    try {
      await client.connect();

      if (client.connectionStatus!.state == MqttConnectionState.connected) {
        debugPrint("MQTT Connected");

        setState(() {
          mqttConnected = true;
        });
      } else {
        debugPrint(client.connectionStatus.toString());

        client.disconnect();
      }
    } catch (e) {
      debugPrint("MQTT Error : $e");

      client.disconnect();
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("ESP32 Voice Assistant"),
        centerTitle: true,
        backgroundColor: Colors.amberAccent,
      ),
      body: Center(
        child: Padding(
          padding: const EdgeInsets.all(20),
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              Icon(
                isListening ? Icons.mic : Icons.mic_none,
                size: 120,
                color: isListening ? Colors.red : Colors.black,
              ),

              const SizedBox(height: 20),

              Text(
                isListening ? "Listening..." : "Tap the button to speak",
                style: const TextStyle(
                  fontSize: 22,
                  fontWeight: FontWeight.bold,
                ),
              ),

              const SizedBox(height: 30),

              ElevatedButton(
                onPressed: () {
                  if (isListening) {
                    stopListening();
                  } else {
                    startListening();
                  }
                },
                style: ElevatedButton.styleFrom(
                  padding: const EdgeInsets.symmetric(
                    horizontal: 40,
                    vertical: 18,
                  ),
                ),
                child: Text(
                  isListening ? "Stop" : "Start",
                  style: const TextStyle(fontSize: 18),
                ),
              ),

              const SizedBox(height: 30),

              Text(
                "You said:",
                style: TextStyle(
                  fontWeight: FontWeight.bold,
                  color: Colors.grey[700],
                ),
              ),

              const SizedBox(height: 10),

              Text(
                spokenText,
                textAlign: TextAlign.center,
                style: const TextStyle(fontSize: 24),
              ),

              const SizedBox(height: 30),

              Text(
                mqttConnected ? "MQTT Connected" : "MQTT Disconnected",
                style: TextStyle(
                  fontSize: 18,
                  color: mqttConnected ? Colors.green : Colors.red,
                  fontWeight: FontWeight.bold,
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
