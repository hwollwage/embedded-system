import "dotenv/config";
import express from "express";
import mongoose from "mongoose";

const app = express();
const PORT = process.env.PORT || 3000;

app.use(express.json());

mongoose
    .connect("mongodb://root:123@127.0.0.1:27018/supermarket_db?authSource=admin")

app.listen(PORT, () => {
    console.log("app in port 3000");
});