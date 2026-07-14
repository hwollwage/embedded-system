import 'package:flutter/material.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return const MaterialApp(
      debugShowCheckedModeBanner: false,
      home: HomePage(),
    );
  }
}

class HomePage extends StatefulWidget {
  const HomePage({super.key});

  @override
  State<HomePage> createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  int selectedIndex = 0;

  final List<Widget> pages = const [
    Center(
      child: Text(
        "🏠 Home",
        style: TextStyle(fontSize: 30),
      ),
    ),
    Center(
      child: Text(
        "👤 Profile",
        style: TextStyle(fontSize: 30),
      ),
    ),
    Center(
      child: Text(
        "⚙️ Settings",
        style: TextStyle(fontSize: 30),
      ),
    ),
  ];

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        centerTitle: true,
        title: const Text("Navigation Rail"),
      ),

      body: Row(
        children: [
          NavigationRail(
            selectedIndex: selectedIndex,

            onDestinationSelected: (index) {
              setState(() {
                selectedIndex = index;
              });
            },

            labelType: NavigationRailLabelType.all,

            destinations: const [
              NavigationRailDestination(
                icon: Icon(Icons.home_outlined),
                selectedIcon: Icon(Icons.home),
                label: Text("Home"),
              ),

              NavigationRailDestination(
                icon: Icon(Icons.person_outline),
                selectedIcon: Icon(Icons.person),
                label: Text("Profile"),
              ),

              NavigationRailDestination(
                icon: Icon(Icons.settings_outlined),
                selectedIcon: Icon(Icons.settings),
                label: Text("Settings"),
              ),
            ],
          ),

          const VerticalDivider(width: 1),

          Expanded(
            child: pages[selectedIndex],
          ),
        ],
      ),
    );
  }
}