import axios from "axios";
import "dotenv/config";
import express, { response } from "express";
import mongoose from "mongoose";

const app = express();

app.use(express.json());

mongoose
    .connect(process.env.MONGODB_URL);

const qrisSchema = new mongoose.Schema({
    transactionId: {type: String},
    orderId: {type: String},
    acquirer: {type: String}
});

const Qris = mongoose.model("Qris", qrisSchema);

app.post("/create-qris", async (req,res) => {
    try {
        const orderId = `COFFEE-${Date.now()}-${Math.random().toString().slice(2,6)}`;
        const response = await fetch(
            "https://api.sandbox.midtrans.com/v2/charge",
            {
                method: "POST",
                headers: {
                    "Content-Type": "application/json",
                    "Accept": "application/json",
                    "Authorization":
                        "Basic " + Buffer.from(process.env.MIDTRANS_SERVER_KEY + ":")
                        .toString("base64"),
                },
                "body": JSON.stringify({
                    payment_type: "qris",
                    transaction_details: {
                        order_id: orderId,
                        gross_amount: 10000,
                    },
                    qris: {
                        acquirer: "gopay"
                    },
                }),
            }
        );

        const data = await response.json();

        const qris = await Qris.create({
            transactionId: data.transaction_id,
            orderId: data.order_id,
            acquirer: data.acquirer
        });

        res.status(201).json({
            message: "qris created",
            data: qris
        });
        // res.json(data);

    } catch (err) {
        console.error(err);
        res.status(500).json({
            message: "failed to create QRIS"
        })
    }
});

app.get("/api/qris", async (req,res) => {
    try {
        const data = await Qris.find();
        res.status(200).json(data);
    } catch (err) {
        console.error(err);
        res.status(500).json(err);
    }
})

app.get("/rezponze", async (req,res) => {
    const rezponse = await axios.get("http://localhost:3000/api/qris");
    console.log("axios res : ", rezponse.data);
});

app.listen(3000, () => {
    console.log(`app in port 3000`);
});