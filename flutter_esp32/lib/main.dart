import 'package:flutter/material.dart';
// If your HomePage is in a separate file, uncomment the line below:
import 'pages/home_page.dart'; 

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      title: '2x2 Grid Cards',
      theme: ThemeData(
        useMaterial3: true,
        colorScheme: ColorScheme.fromSeed(seedColor: Colors.teal),
      ),
      home: const GridCardScreen(),
    );
  }
}

class GridCardScreen extends StatelessWidget {
  const GridCardScreen({super.key});

  @override
  Widget build(BuildContext context) {
    final List<Map<String, dynamic>> gridData = [
      {'title': 'Analytics', 'icon': Icons.bar_chart, 'color': Colors.blue},
      {'title': 'Messages', 'icon': Icons.mail_outline, 'color': Colors.orange},
      {'title': 'Storage', 'icon': Icons.cloud_queue, 'color': Colors.green},
      {'title': 'Settings', 'icon': Icons.settings, 'color': Colors.purple},
    ];

    return Scaffold(
      appBar: AppBar(
        title: const Text('2x2 Grid Menu'),
        centerTitle: true,
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: GridView.builder(
          shrinkWrap: true, 
          gridDelegate: const SliverGridDelegateWithFixedCrossAxisCount(
            crossAxisCount: 2,
            crossAxisSpacing: 16.0,
            mainAxisSpacing: 16.0,
            childAspectRatio: 1.0, 
          ),
          itemCount: gridData.length,
          itemBuilder: (context, index) {
            final item = gridData[index];
            return Card(
              elevation: 3.0,
              shape: RoundedRectangleBorder(
                borderRadius: BorderRadius.circular(16.0),
              ),
              clipBehavior: Clip.hardEdge, 
              child: InkWell(
                onTap: () {
                  // Checks if it is the first card (index 0)
                  if (index == 0) {
                    Navigator.push(
                      context,
                      MaterialPageRoute(builder: (context) => const HomePage()),
                    );
                  } else {
                    ScaffoldMessenger.of(context).showSnackBar(
                      SnackBar(content: Text('${item['title']} selected')),
                    );
                  }
                },
                child: Padding(
                  padding: const EdgeInsets.all(16.0),
                  child: Column(
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: [
                      CircleAvatar(
                        radius: 28,
                        backgroundColor: item['color'].withAlpha(30),
                        child: Icon(
                          item['icon'],
                          size: 30,
                          color: item['color'],
                        ),
                      ),
                      const SizedBox(height: 14),
                      Text(
                        item['title'],
                        style: const TextStyle(
                          fontSize: 16,
                          fontWeight: FontWeight.bold,
                        ),
                      ),
                    ],
                  ),
                ),
              ),
            );
          },
        ),
      ),
    );
  }
}

// Temporary placeholder target widget (Move this into home_page.dart file if needed)
// class HomePage extends StatelessWidget {
//   const HomePage({super.key});

//   @override
//   Widget build(BuildContext context) {
//     return Scaffold(
//       appBar: AppBar(
//         title: const Text('Home Page'),
//       ),
//       body: const Center(
//         child: Text(
//           'Welcome to the Home Page!',
//           style: TextStyle(fontSize: 20, fontWeight: FontWeight.bold),
//         ),
//       ),
//     );
//   }
// }
