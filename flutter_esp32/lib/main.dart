import 'package:flutter/material.dart';
import 'package:google_fonts/google_fonts.dart';
// import 'package:mqtt_client/mqtt_client.dart';
// import 'package:mqtt_client/mqtt_server_client.dart';
import 'package:flutter_local_notifications/flutter_local_notifications.dart';
import 'dart:io';
import 'pages/home_page.dart';
import 'pages/buzzer_page.dart';
import 'pages/led_page.dart';
import 'pages/servo_page.dart';
import 'pages/gas_page.dart';

final FlutterLocalNotificationsPlugin notifications =
  FlutterLocalNotificationsPlugin();

Future<void> main() async {
  WidgetsFlutterBinding.ensureInitialized();

  const AndroidInitializationSettings androidSettings = 
    AndroidInitializationSettings('@mipmap/ic_launcher');
  
  const InitializationSettings settings =
    InitializationSettings(android: androidSettings);
  
  await notifications.initialize(settings);

  if(Platform.isAndroid) {
    await notifications.resolvePlatformSpecificImplementation
    <AndroidFlutterLocalNotificationsPlugin>()
    ?.requestExactAlarmsPermission();
  }

  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({super.key});

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {

  Future<void> showNotification() async {
    const AndroidNotificationDetails androidDetails = 
      AndroidNotificationDetails(
        'Hanzel Channel 1',
        'Test Notif',
        channelDescription: 'Hanzel CH1',
        importance: Importance.high,
        priority: Priority.high,
      );

    const NotificationDetails details =
      NotificationDetails(android: androidDetails);

    await notifications.show(0, "ESP32 FLUTTER", "Something changed", details,);
  }

  int currentIndex = 1;
  
  final List<Widget> pages = const [
    LedPage(),
    ServoPage(),
    HomePage(),
    BuzzerPage(),
    GasPage(),
  ];

  final List<String> titles = [
    "LED",
    'SERVO',
    'HOME',
    'BUZZER',
    'GAS',
  ];

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: Scaffold(
        appBar: AppBar(
          centerTitle: true,
          backgroundColor: Colors.cyanAccent,
          title: Text(
            "ESP32 Pages",
            style: GoogleFonts.jetBrainsMono(
              color: Colors.black,
              fontSize: 24,
              fontWeight: FontWeight.bold,
            ),
          ),
        ),

        body: pages[currentIndex],

        bottomNavigationBar: BottomNavigationBar(
          currentIndex: currentIndex,
          onTap: (index) {
            setState(() {
              currentIndex = index;
            });
          },
          items: const [
            BottomNavigationBarItem(
              icon: Icon(Icons.lightbulb),
              label: "LED",
            ),
            BottomNavigationBarItem(
              icon: Icon(Icons.precision_manufacturing),
              label: "SERVO",
            ),
            BottomNavigationBarItem(
              icon: Icon(Icons.home),
              label: "HOME",
            ),
            BottomNavigationBarItem(
              icon: Icon(Icons.spatial_audio_off),
              label: "BUZZER",
            ),
            BottomNavigationBarItem(
              icon: Icon(Icons.thermostat),
              label: "GAS",
            ),
          ],
          backgroundColor: Colors.white,
          selectedFontSize: 17,
          unselectedFontSize: 13,
          selectedItemColor: Colors.black,
          unselectedItemColor: Colors.grey,
          type: BottomNavigationBarType.fixed,

        ),

        floatingActionButton: FloatingActionButton(
          onPressed: showNotification,
          child: const Icon(Icons.notifications),
        ),
      ),
    );
  }
}
