import express, { Router } from "express";
import {
    createGasData,
    getGasData,
    deleteGasData,
    updateGasData,
    getLatestGasData
} from "../controllers/gas.controller.js";

const router = express.Router();

router.post("/", createGasData);
router.get("/", getGasData);
router.delete("/:id", deleteGasData);
router.put("/:id", updateGasData);
router.patch("/:id", updateGasData);
router.get("/latest", getLatestGasData);

export default router;