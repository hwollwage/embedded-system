import express from "express";
import { createRadioScan, getRadioScan } from "../controllers/radio.controller";

const router = express.Router();

router.post("/", createRadioScan);
router.get("/", getRadioScan);

export default router;