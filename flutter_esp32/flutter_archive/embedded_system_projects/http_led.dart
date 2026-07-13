import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return const MaterialApp(
      home: HomePage(),
      debugShowCheckedModeBanner: false,
    );
  }
}

class HomePage extends StatelessWidget {
  const HomePage({super.key});

  static const String espIP = "192.168.0.100";

  Future<void> ledOn() async {
    await http.get(Uri.parse("http://$espIP/on"));
  }

  Future<void> ledOff() async {
    await http.get(Uri.parse("http://$espIP/off"));
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("ESP32 ddd LED"),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [

            ElevatedButton(
              onPressed: ledOn,
              child: const Text("Turn ON"),
            ),

            const SizedBox(height: 20),

            ElevatedButton(
              onPressed: ledOff,
              child: const Text("Turn OFF"),
            ),
          ],
        ),
      ),
    );
  }
}