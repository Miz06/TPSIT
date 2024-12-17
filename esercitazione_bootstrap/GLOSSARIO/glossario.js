document.addEventListener("DOMContentLoaded", function () {
    // Funzione per caricare i dati dal file JSON
    fetch('glossario.json')
        .then(response => response.json())
        .then(data => {
            const container = document.querySelector('.container .row .col-md-12');

            // Navbar
            const navbarBrand = document.querySelector('.navbar-brand');
            navbarBrand.textContent = data.navbar.brand;
            const navbarLinks = document.querySelector('.navbar-nav');
            data.navbar.links.forEach(link => {
                const listItem = document.createElement('li');
                listItem.classList.add('nav-item');
                const anchor = document.createElement('a');
                anchor.classList.add('nav-link', 'text-dark');
                anchor.href = link.href;
                anchor.textContent = link.text;
                listItem.appendChild(anchor);
                navbarLinks.appendChild(listItem);
            });

            // Aggiungi ciascun termine e definizione al container
            data.glossary.forEach(item => {
                const glossaryItem = document.createElement('div');
                glossaryItem.classList.add('glossary-definition');

                const term = document.createElement('span');
                term.classList.add('glossary-term');
                term.textContent = item.term + ':';

                const definition = document.createElement('p');
                definition.textContent = item.definition;

                glossaryItem.appendChild(term);
                glossaryItem.appendChild(definition);

                container.appendChild(glossaryItem);
            });

            // Footer
            const footer = document.querySelector('footer p');
            footer.textContent = data.footer.text;
        })
        .catch(error => {
            console.error("Errore nel caricamento del file JSON:", error);
        });
});