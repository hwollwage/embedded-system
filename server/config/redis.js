import { createClient } from "redis";

const redisClient = createClient({
    url: "redis://localhost:6379"
});

redisClient.on("error", (err) => {
    console.error("redis error: ",err);
});

await redisClient.connect();
console.log("redis connected");

export default redisClient;