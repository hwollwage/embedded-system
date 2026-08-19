import 'package:flutter/material.dart';

void main() => runApp(MyApp());

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

class HomePage extends StatelessWidget {
  const HomePage({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        centerTitle: true,
        title: const Text("SNACKBAR EXAMPLE"),
        backgroundColor: Colors.amberAccent,
      ),

      body: Center(
        child: ElevatedButton(
          onPressed: () {
            ScaffoldMessenger.of(context).showSnackBar(
              SnackBar(
                
                // REQUIRE => content: Text()
                content: Text("BUTTON CLICKED", textAlign: TextAlign.center,),
                
                // MAKE FLOAT SNACKBAR
                behavior: SnackBarBehavior.floating,

                // ROUNDED SNACKBAR
                shape: RoundedRectangleBorder(
                  borderRadius: BorderRadius.circular(15),
                ),

                // MARGIN
                margin: EdgeInsets.symmetric(
                  horizontal: 40,
                  vertical: 20,
                ),

                // DURATION SNACKBAR
                duration: const Duration(seconds: 1),
              ),
            );
          },
          style: ElevatedButton.styleFrom(
            fixedSize: Size(200, 50),
            backgroundColor: const Color.fromARGB(255, 70, 44, 10)
          ),
          child: const Text(
            "SHOW SNACK BAR",
            style: TextStyle(
              color: Colors.white,
            ),
          ),
        ),
      ),
    );
  }
}