import 'package:flutter/material.dart';

class TestPage extends StatefulWidget {
  const TestPage({super.key});

  @override
  State<TestPage> createState() => _TestPageState();
}

class _TestPageState extends State<TestPage> {
  // Application state tracked dynamically inside the Stateful widget
  String _selectedFeature = 'None';
  int _interactionCount = 0;

  final List<Map<String, dynamic>> _gridData = [
    {'title': 'Analytics', 'icon': Icons.bar_chart, 'color': Colors.blue},
    {'title': 'Messages', 'icon': Icons.mail_outline, 'color': Colors.orange},
    {'title': 'Storage', 'icon': Icons.cloud_queue, 'color': Colors.green},
    {'title': 'Settings', 'icon': Icons.settings, 'color': Colors.purple},
  ];

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Stateful Grid'),
        centerTitle: true,
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.stretch,
          children: [
            // State display card header
            Card(
              color: Theme.of(context).colorScheme.primaryContainer,
              child: Padding(
                padding: const EdgeInsets.all(16.0),
                child: Column(
                  children: [
                    Text(
                      'Active Panel: $_selectedFeature',
                      style: const TextStyle(fontSize: 18, fontWeight: FontWeight.bold),
                    ),
                    const SizedBox(height: 4),
                    Text('Total Actions Triggered: $_interactionCount'),
                  ],
                ),
              ),
            ),
            const SizedBox(height: 24),
            
            // 2x2 Grid using State triggers
            Expanded(
              child: GridView.builder(
                gridDelegate: const SliverGridDelegateWithFixedCrossAxisCount(
                  crossAxisCount: 2,
                  crossAxisSpacing: 16.0,
                  mainAxisSpacing: 16.0,
                  childAspectRatio: 1.0,
                ),
                itemCount: _gridData.length,
                itemBuilder: (context, index) {
                  final item = _gridData[index];
                  final bool isSelected = _selectedFeature == item['title'];

                  return Card(
                    elevation: isSelected ? 8.0 : 2.0,
                    // Highlight the container border if selected
                    shape: RoundedRectangleBorder(
                      borderRadius: BorderRadius.circular(16.0),
                      side: isSelected
                          ? BorderSide(color: item['color'], width: 3.0)
                          : BorderSide.none,
                    ),
                    clipBehavior: Clip.hardEdge,
                    child: InkWell(
                      onTap: () {
                        // Mutate state within setState to schedule a framework redraw
                        setState(() {
                          _selectedFeature = item['title'];
                          _interactionCount++;
                        });
                      },
                      child: Padding(
                        padding: const EdgeInsets.all(16.0),
                        child: Column(
                          mainAxisAlignment: MainAxisAlignment.center,
                          children: [
                            CircleAvatar(
                              radius: 28,
                              backgroundColor: item['color'].withAlpha(isSelected ? 60 : 25),
                              child: Icon(
                                item['icon'],
                                size: 30,
                                color: item['color'],
                              ),
                            ),
                            const SizedBox(height: 14),
                            Text(
                              item['title'],
                              style: TextStyle(
                                fontSize: 16,
                                
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
          ],
        ),
      ),
    );
  }
}
