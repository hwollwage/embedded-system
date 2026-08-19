


async function getUser(id) {
    const response = await fetch(
        `https://jsonplaceholder.typicode.com/users/${id}`
    );

    if(!response.ok) {
        throw new Error("gagal mengambil data");
    }

    return await response.json();
}

async function main() {
    try {
        const user = await getUser(1);
        console.log("ID : ", user.id);
        console.log("name : ", user.name);
        console.log("steet : ", user.address.street);
    } catch (error) {
        console.log(error.message);
    }
}

main();