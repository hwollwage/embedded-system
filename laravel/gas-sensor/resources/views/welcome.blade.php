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
                <th>Device ID</th>
                <th>Gas Level</th>
                <th>Alarm Status</th>
                <th>Time</th>
            </tr>
        </thead>
        <tbody>
            @foreach($readings as $reading)
            <tr class="{{ $reading->alarm ? 'table-danger' : '' }}">
                <td>{{ $reading->device_id }}</td>
                <td>{{ $reading->gas_value }} ppm</td>
                <td>{{ $reading->alarm ? '🚨 TRIGGERED' : '✅ Clear' }}</td>
                <td>{{ $reading->created_at->diffForHumans() }}</td>
            </tr>
            @endforeach
        </tbody>
    </table>
</body>
</html>
