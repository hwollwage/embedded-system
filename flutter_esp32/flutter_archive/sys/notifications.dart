import 'package:flutter/material.dart';
// import 'package:google_fonts/google_fonts.dart';
// import 'package:mqtt_client/mqtt_client.dart';
// import 'package:mqtt_client/mqtt_server_client.dart';
import 'dart:io';
import 'package:flutter_local_notifications/flutter_local_notifications.dart';

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
    await notifications.resolvePlatformSpecificImplementation<
    AndroidFlutterLocalNotificationsPlugin>()
    ?.requestNotificationsPermission();
  }
}
// class ServoPage extends StatefulWidget {
//   const ServoPage({super.key});

//   @override
//   State<ServoPage> createState() => _ServoPageState();
// }

// class _ServoPageState extends State<ServoPage> {

  Future<void> showNotification() async {
    const AndroidNotificationDetails androidDetails =
      AndroidNotificationDetails(
        'test_channel',
        'test notif',
        channelDescription: 'testing notifications',
        importance: Importance.high,
        priority: Priority.high,
      );

    const NotificationDetails details =
      NotificationDetails(android: androidDetails);

    await notifications.show(
      0,
      'GRAB MAS...',
      'masuk aja mas,🗣️🗣️',
      details,
    );
  }
// }