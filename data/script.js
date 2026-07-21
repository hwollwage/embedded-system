const mic = document.getElementById("mic");
const status = document.getElementById("status");
const result = document.getElementById("result");

const SpeechRecognition =
    window.SpeechRecognition ||
    window.webkitSpeechRecognition;

if(!SpeechRecognition) {
    status.innerHTML = "speech recg is not supported";
}else {
    const recognition = new SpeechRecognition();
    recognition.lang = "en.US";
    recognition.interimResults = false;
    recognition.continuous = false;

    mic.onclick = () => {
        status.innerHTML = "listening...";
        recognition.start();
    };

    recognition.onresult = (event) => {
        const text =
    }

    // MALES ANJG js ktl
}