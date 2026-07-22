import 'package:flutter/material.dart';

class TestPage extends StatefulWidget {
  const TestPage({super.key});

  @override
  State<TestPage> createState() => _TestPageState();
}

class _TestPageState extends State<TestPage> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text("flutt"), centerTitle: true),
      body: Padding(
        padding: const EdgeInsets.all(10),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.stretch,
          children: [
            Card(
              // 1. Clips the splash effect to the Card's border radius
              clipBehavior: Clip.antiAlias,
              shape: RoundedRectangleBorder(
                borderRadius: BorderRadius.circular(12),
              ),
              child: InkWell(
                // 2. Triggers the action when tapped
                onTap: () {
                  // Add your tap logic here
                  print("fewkoweof");
                  ScaffoldMessenger.of(
                    context,
                  ).showSnackBar(SnackBar(content: Text("eowkfwoekf")));
                },
                child: const Column(
                  children: [
                    ListTile(
                      leading: Icon(Icons.cell_tower_outlined),
                      title: Text("hello"),
                      subtitle: Text("qweoqw"),
                    ),
                  ],
                ),
              ),
            ),

            const SizedBox(height: 20),

            Card(
              clipBehavior: Clip.none,
              shape: RoundedRectangleBorder(
                borderRadius: BorderRadiusGeometry.circular(15),
                side: BorderSide(color: Colors.black),
              ),
              color: Colors.amber,
              child: InkWell(
                onTap: () {
                  ScaffoldMessenger.of(
                    context,
                  ).showSnackBar(SnackBar(content: Text("qqqq")));
                },
                child: const Column(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: [
                    ListTile(
                      leading: Icon(Icons.computer),
                      title: Text("qqq"),
                      subtitle: Text("xx"),
                    ),
                  ],
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}
