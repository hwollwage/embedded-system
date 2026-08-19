import 'package:flutter/material.dart';
import 'package:google_fonts/google_fonts.dart';

import 'main_page.dart';

class ProfilePage extends StatelessWidget {
  const ProfilePage({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      drawer: buildAppDrawer(context),

      appBar: AppBar(
        backgroundColor: Colors.amber,
        centerTitle: true,
        title: Text(
          "Profile",
          style: GoogleFonts.jetBrainsMono(
            fontWeight: FontWeight.bold,
          ),
        ),
      ),

      body: Center(
        child: Text(
          "👤 Profile Page",
          style: GoogleFonts.jetBrainsMono(
            fontSize: 30,
            fontWeight: FontWeight.bold,
          ),
        ),
      ),
    );
  }
}