import Gas from "../models/gas.model.js";
import redisClient from "../config/redis.js";

// GET LATEST DATA REDIS
export const getLatestGasData = async (req, res) => {
    try {
        const keys = await redisClient.keys("gas:*");
        const data = [];

        for(const key of keys) {
            const value = await redisClient.get(key);
            if(value) {
                data.push(JSON.parse(value));
            }
        }

        res.status(200).json({
            message: "latest gas data retrieved",
            data
        });

    } catch (err) {
        res.status(500).json({
            message: "failed to get latest gas data",
            error: err.message
        });
    }
}

// POST CREATE
export const createGasData = async (req, res) => {
    try {
        const gas = await Gas.create(req.body);

        /// REDIS

        await redisClient.set(
            `gas:${req.body.deviceId}`, JSON.stringify(req.body)
        );

        res.status(201).json({
            message: "gas data created",
            data: gas
        });

    } catch (err) {
        res.status(500).json({
            message: "failed to create gas data",
            error: err.message
        });
    }
}

// GET DATA
export const getGasData = async (req,res) => {
    try {
        const gasData = await Gas.find().sort({ _id: -1 });

        res.status(200).json({
            message: "gas data retrieved",
            data: gasData
        });

    } catch (err) {
        res.status(500).json({
            message: "failed to get gas data",
            error: err.message
        });
    }
}

// DELETE DATA
export const deleteGasData = async (req,res) => {
    try {
        const { id } = req.params;
        const gas = await Gas.findByIdAndDelete(id);

        if(!gas) {
            res.status(404).json({
                message: "gas data not found"
            });
        }

        res.status(200).json({
            message: "data deleted",
            data: gas
        });

    } catch (err) {
        res.status(500).json({
            message: "failed to delete data",
            error: err.message
        });
    }
}

export const updateGasData = async (req,res) => {
    try {
        const { id } = req.params;
        const gas = await Gas.findByIdAndUpdate(
            id,
            req.body,
            {returnDocument: "after"}
        );

        if(!gas) {
            res.status(404).json({
                message: "data not found to be updated",
            });
        }

        res.status(200).json({
            message: "gas data updated",
            data: gas
        });

    } catch (err) {
        res.status(500).json({
            message: "failed to update gas data",
            error: err.message
        });
    }
}

// === POST ===
// app.post(`/users`, async (req, res) => {
//     const user = new User({
//         name: req.body.name,
//         age: req.body.age,
//         email: req.body.email
//     });

//     await user.save();
//     res.json(user);
// });


// === GET ===
// app.get(`/users`, async (req, res) => {
//     const users = await User.find();
//     res.json(users);
// });