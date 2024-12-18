// Carica i dati JSON e genera il contenuto
fetch('informatica.json')
  .then(response => {
    if (!response.ok) {
      throw new Error(`Errore nel caricamento del JSON: ${response.statusText}`);
    }
    return response.json();
  })
  .then(data => {
    // Genera dinamicamente la navbar
    const navbarBrand = document.getElementById("navbar-brand");
    const navbarLinks = document.getElementById("navbar-links");

    navbarBrand.textContent = data.navbar.brand;
    data.navbar.links.forEach(link => {
      const listItem = document.createElement("li");
      listItem.className = "nav-item";

      const anchor = document.createElement("a");
      anchor.className = "nav-link text-dark";
      anchor.href = link.href;
      anchor.textContent = link.text;

      listItem.appendChild(anchor);
      navbarLinks.appendChild(listItem);
    });

    // Genera dinamicamente le sezioni
    const mainContent = document.getElementById("main-content");

    data.sections.forEach(section => {
      const sectionCard = document.createElement("div");
      sectionCard.className = "card text-center mt-5 shadow";

      const cardHeader = document.createElement("div");
      cardHeader.className = "card-header";
      cardHeader.textContent = section.title;

      const cardBody = document.createElement("div");
      cardBody.className = "d-flex align-items-center p-4";
      cardBody.style.backgroundColor = "rgb(248, 248, 248)";

      const image = document.createElement("img");
      image.src = section.image;
      image.className = "img-fluid flex-shrink-0 me-4";
      image.style.width = "40%";
      image.alt = section.title;

      const textDiv = document.createElement("div");
      const description = document.createElement("p");
      description.className = "mt-4";
      description.style.fontSize = "1.1rem";
      description.style.lineHeight = "1.5";
      description.textContent = section.description;

      textDiv.appendChild(description);
      cardBody.appendChild(image);
      cardBody.appendChild(textDiv);

      sectionCard.appendChild(cardHeader);
      sectionCard.appendChild(cardBody);

      const stepsRow = document.createElement("div");
      stepsRow.className = "row row-cols-1 row-cols-sm-2 row-cols-md-3 g-4 mt-3";

      section.steps.forEach(step => {
        const stepCol = document.createElement("div");
        stepCol.className = "col";

        const stepCard = document.createElement("div");
        stepCard.className = "card border-dark mb-3 hover-effect";

        const stepCardBody = document.createElement("div");
        stepCardBody.className = "card-body shadow";

        const stepTitle = step.title ? `<h5 class="card-title">${step.title}</h5>` : "";
        stepCardBody.innerHTML = `${stepTitle}<p class="card-text">${step.description}</p>`;

        stepCard.appendChild(stepCardBody);
        stepCol.appendChild(stepCard);
        stepsRow.appendChild(stepCol);
      });

      mainContent.appendChild(sectionCard);
      mainContent.appendChild(stepsRow);
    });

    // Aggiorna il footer
    const footerText = document.getElementById("footer-text");
    footerText.textContent = data.footer.text;
  })
  .catch(error => {
    console.error("Errore durante il caricamento del JSON:", error);
  });
