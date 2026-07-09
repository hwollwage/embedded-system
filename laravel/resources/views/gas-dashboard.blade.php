<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>ROOT</title>
    <style>
        /* Adds borders to the table and cells */
        table {
            border-collapse: collapse; /* Prevents double borders */
            width: 100%;
        }
        
        table, th, td {
            border: 1px solid #ccc; /* Border thickness, style, and color */
        }

        th, td {
            padding: 10px; /* Optional: Adds spacing inside cells for better readability */
            text-align: left;
        }

        /* Retains compatibility with your Blade conditional styling */
        .table-danger {
            background-color: #f8d7da;
        }
    </style>
</head>
<body>
    <h1>SENSOR DASHBOARD</h1><br>
    <h2>Gas Sensor Dashboard</h2>
    <table>
        <thead>
            <tr>
                <th>ID</th>
                <th>Device</th>
                <th>Gas</th>
                <th>Alarm</th>
                <th>RSSI</th>
                <th>IP Address</th>
                <th>Free Heap</th>
                <th>Uptime</th>
                <th>Created At</th>
                <th>Created</th>
            </tr>
        </thead>
        <tbody>
            @foreach($readings as $reading)
            <tr class="{{ $reading->alarm ? 'table-danger' : '' }}">
               <td>{{ $reading->id }}</td>
               <td>{{ $reading->device_id }}</td>
               <td>{{ $reading->gas_value }}</td>
               <td>{{ $reading->alarm ? '🚨 DETECTED' : '✅ SAFE' }}</td>
               <td>{{ $reading->wifi_rssi }} dBm</td>
               <td>{{ $reading->ip_address }}</td>
               <td>{{ number_format($reading->free_heap) }}</td>
               <td>{{ round($reading->uptime_ms / 1000) }} s</td>
               <td>{{ $reading->created_at->diffForHumans() }}</td>
               <td>{{ $reading->created_at->format('H:i:s') }}</td>
            </tr>
            @endforeach
        </tbody>
    </table>
</body>
</html>