import 'package:flutter/material.dart';

class HomePage extends StatelessWidget {
  const HomePage({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: Scaffold(
        appBar: AppBar(
          centerTitle: true,
          backgroundColor: Colors.amber,
          title: Text("home page"),
        ),
        body: Center(
          child: ElevatedButton(
            onPressed: () {
              print("test");
            },
            child: Text("click me"),
          ),
        ),
      ),
    );
  }
}