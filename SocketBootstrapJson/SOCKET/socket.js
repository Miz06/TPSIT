document.addEventListener("DOMContentLoaded", () => {
    fetch("./socket.json")
        .then(response => response.json())  // Converte la risposta in formato JSON
        .then(data => {
            // === SEZIONE NAVBAR ===
            const navbarBrand = document.querySelector(".navbar-brand");
            navbarBrand.textContent = data.navbar.brand;

            const navbarLinks = document.querySelector(".navbar-nav");
            data.navbar.links.forEach(link => {
                const li = document.createElement("li");
                li.className = "nav-item";

                const a = document.createElement("a");
                a.className = "nav-link text-dark";
                a.href = link.href;
                a.textContent = link.text;

                li.appendChild(a);
                navbarLinks.appendChild(li);
            });

            // === SEZIONE INTRO CARD ===
            const container = document.querySelector(".container");
            const introCard = document.createElement("div");
            introCard.className = "card text-center mt-5 me-5 ms-5 shadow";

            const introCardHeader = document.createElement("div");
            introCardHeader.className = "card-header";
            introCardHeader.style.fontSize = "1.2rem";
            introCardHeader.style.fontWeight = "bold";
            introCardHeader.textContent = data.introCard.header;

            const introCardBody = document.createElement("div");
            introCardBody.className = "d-flex align-items-center p-4";
            introCardBody.style.backgroundColor = "rgb(248, 248, 248)";

            const introImage = document.createElement("img");
            introImage.src = data.introCard.image;
            introImage.alt = data.introCard.alt;
            introImage.className = "img-fluid flex-shrink-0 me-4";
            introImage.style.width = "40%";

            const introText = document.createElement("div");
            introText.innerHTML = `<p class="mt-4" style="font-size: 1.1rem; line-height: 1.5;">${data.introCard.description}</p>`;

            introCardBody.appendChild(introImage);
            introCardBody.appendChild(introText);
            introCard.appendChild(introCardHeader);
            introCard.appendChild(introCardBody);
            container.appendChild(introCard);

            // === AGGIUNTA <hr> ===
            const hr1 = document.createElement("hr");
            hr1.className = "my-hr";
            hr1.style.margin = "2%";
            container.appendChild(hr1);

            // === SEZIONE CARDS ===
            // Crea il primo contenitore per le card
            const row1 = document.createElement("div");
            row1.className = "row justify-content-center";

            container.appendChild(row1);

            const firstTwoCards = data.cards.slice(0, 2);

            // Aggiungi le prime due card al primo contenitore
            firstTwoCards.forEach(card => {
                const col = document.createElement("div");
                col.className = "col-12 col-md-6 mb-4";

                const cardElement = document.createElement("div");
                cardElement.className = "card shadow";

                const cardHeader = document.createElement("div");
                cardHeader.className = "card-header";
                cardHeader.innerHTML = `<h5 class="mb-0">${card.title}</h5>`;

                const cardBody = document.createElement("div");
                cardBody.className = "card-body";

                const list = document.createElement("ol");
                card.content.forEach(item => {
                    const listItem = document.createElement("li");
                    listItem.textContent = item;
                    list.appendChild(listItem);
                });

                const example = document.createElement("span");
                example.className = "example";
                example.innerHTML = "<strong>Esempio:</strong> <span style='font-weight: bold; color: black;'>" + card.example + "</span>";

                cardBody.appendChild(list);
                cardBody.appendChild(example);
                cardElement.appendChild(cardHeader);
                cardElement.appendChild(cardBody);
                col.appendChild(cardElement);
                row1.appendChild(col);
            });

            // === AGGIUNTA <hr> ===
            const hr2 = document.createElement("hr");
            hr2.className = "my-hr";
            hr2.style.margin = "1%";
            container.appendChild(hr2);

            // === SEZIONE CODICI CLIENT E SERVER ===
            const codeExamplesSection = document.createElement("div");
            codeExamplesSection.className = "mt-5";

            const clientCodeSection = document.createElement("div");
            clientCodeSection.className = "mb-4";
            const clientCodeTitle = document.createElement("h3");
            clientCodeTitle.textContent = "Client Code";
            const clientCode = document.createElement("pre");
            clientCode.textContent = data.codeExamples.client;

            clientCodeSection.appendChild(clientCodeTitle);
            clientCodeSection.appendChild(clientCode);

            const serverCodeSection = document.createElement("div");
            serverCodeSection.className = "mb-4";
            const serverCodeTitle = document.createElement("h3");
            serverCodeTitle.textContent = "Server Code";
            const serverCode = document.createElement("pre");
            serverCode.textContent = data.codeExamples.server;

            serverCodeSection.appendChild(serverCodeTitle);
            serverCodeSection.appendChild(serverCode);

            codeExamplesSection.appendChild(clientCodeSection);
            codeExamplesSection.appendChild(serverCodeSection);
            container.appendChild(codeExamplesSection);

            // === AGGIUNTA <hr> ===
            const hr3 = document.createElement("hr");
            hr3.className = "my-hr";
            hr3.style.margin = "2%";
            container.appendChild(hr3);

            // === SECONDO CONTENITORE PER LE CARD ===
            const row2 = document.createElement("div");
            row2.className = "row justify-content-center";
            container.appendChild(row2);

            const secondTwoCards = data.cards.slice(2, 4);

            // Aggiungi le seconde due card al secondo contenitore
            secondTwoCards.forEach(card => {
                const col = document.createElement("div");
                col.className = "col-12 col-md-6 mb-4";

                const cardElement = document.createElement("div");
                cardElement.className = "card shadow";

                const cardHeader = document.createElement("div");
                cardHeader.className = "card-header";
                cardHeader.innerHTML = `<h5 class="mb-0">${card.title}</h5>`;

                const cardBody = document.createElement("div");
                cardBody.className = "card-body";

                const list = document.createElement("ol");
                card.content.forEach(item => {
                    const listItem = document.createElement("li");
                    listItem.textContent = item;
                    list.appendChild(listItem);
                });

                const example = document.createElement("span");

                cardBody.appendChild(list);
                cardBody.appendChild(example);
                cardElement.appendChild(cardHeader);
                cardElement.appendChild(cardBody);
                col.appendChild(cardElement);
                row2.appendChild(col);
            });

            // === SEZIONE FOOTER ===
            const footer = document.querySelector("footer .text-center p");
            footer.textContent = data.footer.text;
        })
        .catch(error => console.error("Errore nel caricamento dei dati JSON:", error));  // Gestione degli errori
});
