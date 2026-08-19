import express from "express";

const router = express.Router();

router.get("/", (req,res) => {
    res.sendFile("gas.html", {
        root: "public"
    });
});

export default router;