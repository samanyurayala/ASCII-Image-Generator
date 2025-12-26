window.addEventListener("load", (event) => {
    const poller = setInterval(() => {
        const qtWindow = document.getElementById("screen")
                             .querySelector("#qt-shadow-container")
                             .shadowRoot.querySelector("[id^='qt-screen-']")
                             .querySelector("[id^='qt-window-']");
        if (!qtWindow) {
            console.log("Test");
            return
        }

        clearInterval(poller);
        console.log("Test2")
        const mediaQuery = window.matchMedia("(max-width: 800px)");

        function changeViewport(e) {
            if (e.matches) {
                qtWindow.style.transformOrigin = "top left";
                qtWindow.style.transform = "scale(0.5)";
            } else {
                qtWindow.style.transformOrigin = "center center";
                qtWindow.style.transform = "scale(1.0)"
            }
        }

        mediaQuery.addEventListener("change", changeViewport);
        changeViewport(mediaQuery);
    }, 25);
});