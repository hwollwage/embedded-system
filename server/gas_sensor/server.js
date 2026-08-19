import "dotenv/config";
import express from "express";

import connectDB from "./db.js";
import dashboardRoute from "./routes/dashboard.route.js";
import gasRoute from "./routes/gas.route.js";

const PORT = process.env.PORT || 3000;
const app = express();

connectDB();

app.use(express.json());

app.use("/", dashboardRoute)
app.use("/api/gas", gasRoute);

app.listen(PORT, () => {
    console.log(`server at ${PORT}`);
});

