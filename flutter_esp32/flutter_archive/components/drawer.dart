import 'package:flutter/material.dart';
// import 'package:google_fonts/google_fonts.dart';

void main() => runApp(MyApp());

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

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("DRAWER LIST_TILE"),
        centerTitle: true,
      ),

      drawer: Drawer(
        child: ListView(
          padding: EdgeInsets.zero,
          children: [
            const DrawerHeader(
              decoration: BoxDecoration(
                color: Colors.blue,
              ),
              child: Center(
                child: Text(
                  "My Drawer",
                  style: TextStyle(color: Colors.white, fontSize: 24,),
                ),
              ),
            ),

            ListTile(
              leading: const Icon(Icons.home),
              title: Text("HOME"),
              onTap: () {
                print("home");
              },
            ),
            ListTile(
              leading: const Icon(Icons.settings),
              title: Text("SETTINGS"),
              onTap: () {
                print("SETTINGS");
              },
            ),
            ListTile(
              leading: const Icon(Icons.person_2_outlined),
              title: Text("PROFILE"),
              onTap: () {
                print("PROFILE");
              },
            ),
          ],
        ),
      ),
    );
  }
}