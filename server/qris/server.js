import "dotenv/config";
import express, { response } from "express";

const app = express();

app.use(express.json());

let transactionId = null;

app.post("/create-qris", async (req,res) => {
    try {
        const orderId = `TEA-${Date.now()}`;
        const response = await fetch(
            "https://api.sandbox.midtrans.com/v2/charge",
            {
                method: "POST",
                headers: {
                    "Content-Type": "application/json",
                    "Accept": "application/json",
                    "Authorization": "Basic " + Buffer.from(process.env.MIDTRANS_SERVER_KEY + ":").toString("base64"),
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
        res.json(data);
        transactionId = data.transaction_id;

    } catch (err) {
        console.error(err);
        res.status(500).json({
            message: "failed to create QRIS"
        })
    }
});

app.post("/capture-transaction", async (req,res) => {
    try {
        const response = await fetch(
            "https://api.sandbox.midtrans.com/v2/capture",
            {
                method: "POST",
                headers: {
                    "Content-Type": "application/json",
                    "Accept": "application/json",
                    "Authorization": "Basic "+ Buffer.from(process.env.MIDTRANS_SERVER_KEY+":").toString("base64")
                },
                body: JSON.stringify({
                    transaction_id: transactionId,
                    gross_amount: 25000
                })            
            }
        );
    
        const data = await response.json();
        res.json(data);
    } catch (err) {
        console.error(err);
        res.status(500).json({
            message: "error failed to capture transaction"
        });
    }
});

app.get("/register-card", async (req,res) => {
    try {
        const response = await fetch(
            "https://api.sandbox.midtrans.com/v2/card/register",
            {
                method: "GET",
                headers: {
                    "Content-Type": "application/json",
                    "Accept": "application/json",
                    "Authorization": "Basic"+Buffer.from(process.env.MIDTRANS_SERVER_KEY+":").toString("base64")
                },
                body: JSON.stringify({
                    card_number: "123123123123",
                    card_exp_num: "11",
                    card_expr_year: "2027",
                    client_key: process.env.MIDTRANS_SERVER_KEY
                })
            }
        );

        const data = await response.json();
        res.send(data);

    } catch (err) {
        res.status(500).json({
            message: "failed to register card"
        });
    }
});

app.listen(3000, () => {
    console.log(`app in port 3000`);
});