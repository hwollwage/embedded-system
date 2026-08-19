import 'package:flutter/material.dart';
import 'package:flutter_esp32/pages/home.dart';
import 'package:flutter_esp32/pages/profile.dart';
import 'package:flutter_esp32/pages/setting.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({super.key});

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  int currentIdx = 1;

  final List<Widget> pages = const [
    SettingPage(),
    HomePage(),
    ProfilePage(),
  ];

  final List<String> titles = [
    "Setting",
    "Home",
    "Profile",
  ];
  
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: Scaffold(

        body: pages[currentIdx],

        bottomNavigationBar: BottomNavigationBar(
          currentIndex: currentIdx,
          onTap: (value) {
            setState(() {
              currentIdx = value;
            });
          },
          items: [
            BottomNavigationBarItem(
              icon: Icon(currentIdx == 0 ? Icons.settings : Icons.settings_outlined),
              label: "Setting",
            ),

            BottomNavigationBarItem(
              icon: Icon(currentIdx == 1 ? Icons.home : Icons.home_outlined),
              label: "Home",
            ),

            BottomNavigationBarItem(
              icon: Icon(currentIdx == 2 ? Icons.people : Icons.people_outline),
              label: "Profile",
            ),
          ],
        ),
      ),
    );
  }
}