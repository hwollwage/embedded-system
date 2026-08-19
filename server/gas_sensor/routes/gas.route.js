import express from "express";
import {
    createGasData,
    getGasData,
    deleteGasData,
    updateGasData
} from "../controllers/gas.controller.js";

const router = express.Router();

router.post("/", createGasData);
router.get("/", getGasData);
router.delete("/:id", deleteGasData);
router.put("/:id", updateGasData);
router.patch("/:id", updateGasData);

export default router;