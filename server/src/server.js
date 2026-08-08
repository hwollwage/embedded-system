require("dotenv").config();
const express = require("express");
const path = require("path");
const pool = require("./db.js");
const { stat } = require("fs");
const app = express();
const PORT = process.env.PORT || 3000;

app.use(express.json());

app.listen(PORT, () => {
    console.log(`server listening on port ${PORT}`);
});

app.get(`/`, (req, res) => {
    res.sendFile(path.join(__dirname, '..', 'public', 'light.html'));
});

app.get(`/api/light`, async (req, res) => {
    try {
        const [rows] = await pool.execute('SELECT * FROM light_table ORDER BY id DESC LIMIT 50');
        res.status(200).json(rows);
    }catch(err) {
        console.log(`error ${err}`);
        res.status(500).json({
            status: "error",
            message: "failed to retrieve data"
        });
    }
});

app.post(`/api/light`, async (req, res) => {
    try {
        const { analog_light, digital_light, uptime, wifi } = req.body;
        
        const sanitizedAnalog = analog_light !== undefined ? Number(analog_light) : null;
        const sanitizedDigital = digital_light ? 1 : 0;
        const sanitizedUptime = uptime !== undefined ? Number(uptime) : null;
        const rssi = (wifi && wifi.rssi !== undefined) ? Number(wifi.rssi) : null;
        const bssid = (wifi && wifi.bssid) ? String(wifi.bssid).trim() : null;

        const sql = `
            INSERT INTO light_table 
            (analog_light, digital_light, uptime, rssi, bssid)
            VALUES (?, ?, ?, ?, ?)
        `;

        const [result] = await pool.execute(sql, [
            sanitizedAnalog,
            sanitizedDigital,
            sanitizedUptime,
            rssi,
            bssid,
        ]);
        
        console.log(`data saved, row id : ${result.insertId}`);
        
        res.status(201).json({
            status: "success",
            insertId: result.insertId
        });

    }catch(err) {
        console.log(`error : ${err}`);
        res.status(500).json({
            status: "error",
            message: "db insertion failed",
            error_details: err.message
        });
    }
});
