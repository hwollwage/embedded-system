import 'package:flutter/material.dart';
import 'package:web_socket_channel/web_socket_channel.dart';
import 'dart:convert';

class MpuPage extends StatefulWidget {
  // Step 1: Add the function variable to the constructor
  final Function({String? title, String? body}) onTriggerNotification;

  const MpuPage({
    super.key, 
    required this.onTriggerNotification,
  });

  @override
  State<MpuPage> createState() => _MpuPageState();
}

class _MpuPageState extends State<MpuPage> {
  double ax = 0, ay = 0, az = 0;
  double gx = 0, gy = 0, gz = 0;
  double temp = 0;
  late final WebSocketChannel ch;
  String msg = "Waitingx...";

  @override
  void initState() {
    super.initState();
    ch = WebSocketChannel.connect(Uri.parse("ws://192.168.0.105:81"));
    ch.stream.listen(
      (msg) {
        print("Received: $msg");
        try {
          final data = jsonDecode(msg);
          setState(() {
            ax = (data["Ax"] as num).toDouble();
            ay = (data["Ay"] as num).toDouble();
            az = (data["Az"] as num).toDouble();
            gx = (data["Gx"] as num).toDouble();
            gy = (data["Gy"] as num).toDouble();
            gz = (data["Gz"] as num).toDouble();
            temp = (data["temp"] as num).toDouble();
          });

          // Step 2: Trigger the callback passed from main.dart
          if (ax >= 7) {
            widget.onTriggerNotification(
              title: "MPU Alert!",
              body: "Accel X crossed threshold: ${ax.toStringAsFixed(2)}",
            );
          }
        } catch (e) {
          print("JSON Error: $e");
        }
      },
      onError: (error) {
        print("WebSocket Error: $error");
      },
      onDone: () {
        print("WebSocket Closed");
      },
    );
  }

  @override
  void dispose() {
    ch.sink.close();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(centerTitle: true, title: const Text("MPU6050")),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Text("Accel X : ${ax.toStringAsFixed(2)}"),
            Text("Accel Y : ${ay.toStringAsFixed(2)}"),
            Text("Accel Z : ${az.toStringAsFixed(2)}"),
            const SizedBox(height: 20),
            Text("Gyro X : ${gx.toStringAsFixed(2)}"),
            Text("Gyro Y : ${gy.toStringAsFixed(2)}"),
            Text("Gyro Z : ${gz.toStringAsFixed(2)}"),
            const SizedBox(height: 20),
            Text("TEMP : ${temp.toStringAsFixed(2)}°"),
            const SizedBox(height: 20),
            ElevatedButton(
              onPressed: () {
                ch.sink.add("Hello ESP32");
              },
              child: const Text("Sendx"),
            ),
          ],
        ),
      ),
    );
  }
}
