import 'package:flutter/material.dart';
import 'package:google_fonts/google_fonts.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          backgroundColor: Colors.green,
          title: Text(
            "Hello",
            style: GoogleFonts.jetBrainsMono(
              color: Colors.black,
              fontSize: 24,
              fontWeight: FontWeight.bold,
            ),
          ),
          centerTitle: true,
        ),


        body: Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              ElevatedButton(
                onPressed: () {
                  print("1st button clicked");
                },
                style: ElevatedButton.styleFrom(
                  backgroundColor: Colors.yellow,
                ),
                child: Text(
                  "1st button",
                  style: GoogleFonts.jetBrainsMono(
                    color: Colors.black,
                    fontSize: 17,
                    fontWeight: FontWeight.bold,
                  ),
                ),
              ),

              const SizedBox(height: 20,),

              ElevatedButton(
                onPressed: () {
                  print("2nd button clicked");
                },
                style: ElevatedButton.styleFrom(
                  backgroundColor: Colors.green,
                ),
                child: Text(
                  "2nd button",
                  style: GoogleFonts.jetBrainsMono(
                    color: Colors.white,
                    fontSize: 17,
                    fontWeight: FontWeight.bold,
                  ),
                ),
              )

            ],
          ),
        ),


        floatingActionButtonLocation: FloatingActionButtonLocation.endFloat,
        floatingActionButton: Row(
          mainAxisAlignment: MainAxisAlignment.end,
          children: [
            FloatingActionButton.extended(
              onPressed: () {
                print("FAB1 CLICKEED");
              },
              backgroundColor: Colors.redAccent,
              heroTag: "fab1",
              icon: const Icon(
                Icons.add,
                color: Colors.black,
              ),
              label: Text(
                "Add",
                style: GoogleFonts.jetBrainsMono(
                  color: Colors.black,
                  fontWeight: FontWeight.bold,
                ),
              ),
            ),

            const SizedBox(width: 16,),

            FloatingActionButton.extended(
              onPressed: () {
                print("FAB2 CLICJKED");
              },
              backgroundColor: Colors.lightBlueAccent,
              heroTag: "fab2",
              icon: const Icon(
                Icons.remove,
                color: Colors.black,
              ),
              label: Text(
                "Remove",
                style: GoogleFonts.jetBrainsMono(
                  color: Colors.black,
                  fontWeight: FontWeight.bold,
                ),
              ),
            ),
          ],
        ),
        
      ),
    );
  }
}
