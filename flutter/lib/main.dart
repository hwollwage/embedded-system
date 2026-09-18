import 'dart:convert';

import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;

void main() => runApp(const MyApp());

class MyApp extends StatefulWidget {
  const MyApp({super.key});

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  
  List<dynamic> users = [];

  void fetchData() async {
    debugPrint("fetch data");
    const url = "https://jsonplaceholder.typicode.com/users";
    final uri = Uri.parse(url);
    final response = await http.get(uri);
    final body = response.body;
    final json = jsonDecode(body);
    
    setState(() {
      users = json;
    });
  }
  
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: Scaffold(
        appBar: AppBar(
          title: Text("flutter rest api"),
          centerTitle: true,
        ),

        body: users.isEmpty
          ? const Center(child: Text("press button to fetch"),)
          : ListView.builder(
            itemCount: users.length,
            itemBuilder: (context, index) {
              final user = users[index];
              
              final name = user['name'];
              final email = user['email'];

              return ListTile(
                leading: CircleAvatar(
                  child: Text("${index+1}"),
                ),
                title: Text(name.toString()),
                subtitle: Text(email.toString()),
              );
            },
          ),

        floatingActionButton: FloatingActionButton(
          onPressed: fetchData,
          child: const Icon(Icons.download),
        ),
      ),
    );
  }
}

