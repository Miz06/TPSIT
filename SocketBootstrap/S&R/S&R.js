document.addEventListener('DOMContentLoaded', function () {
  fetch('./S&R.json')
    .then(response => response.json())
    .then(data => {
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

      // Modello OSI
      const modelOSI = document.querySelector('#modelOSI-title');
      modelOSI.textContent = data.modelOSI.title;

      const modelOSIImage = document.querySelector('#modelOSI-image');
      modelOSIImage.src = data.modelOSI.imageSrc;
      modelOSIImage.alt = data.modelOSI.imageAlt;

      const modelOSIText = document.querySelector('#modelOSI-text');
      modelOSIText.textContent = data.modelOSI.text;

      // Livelli OSI
      const accordion = document.getElementById('accordionPanelsStayOpenExample');
      data.levels.forEach((level, index) => {
        const item = document.createElement('div');
        item.classList.add('accordion-item');

        const header = document.createElement('h2');
        header.classList.add('accordion-header');

        const button = document.createElement('button');
        button.classList.add('accordion-button', 'collapsed');
        button.type = 'button';
        button.setAttribute('data-bs-toggle', 'collapse');
        button.setAttribute('data-bs-target', `#panelsStayOpen-collapse${index + 1}`);
        button.setAttribute('aria-expanded', 'false');
        button.setAttribute('aria-controls', `panelsStayOpen-collapse${index + 1}`);
        button.textContent = level.title;

        header.appendChild(button);
        item.appendChild(header);

        const collapse = document.createElement('div');
        collapse.id = `panelsStayOpen-collapse${index + 1}`;
        collapse.classList.add('accordion-collapse', 'collapse');

        const body = document.createElement('div');
        body.classList.add('accordion-body');
        body.innerHTML = `<strong>${level.name}</strong>: ${level.description}`;

        collapse.appendChild(body);
        item.appendChild(collapse);
        accordion.appendChild(item);
      });

      // Livello Trasporto
      const transportLayerCardHeader = document.querySelectorAll('.card-header')[1];
      transportLayerCardHeader.textContent = data.transportLayer.title;

      const transportLayerCardBody = transportLayerCardHeader.nextElementSibling;
      const transportLayerText = document.createElement('p');
      transportLayerText.textContent = data.transportLayer.text;
      transportLayerCardBody.appendChild(transportLayerText);

      // Funzionalità Trasporto
      const featureContainer = document.querySelector('.container .row');
      data.features.forEach(feature => {
        const col = document.createElement('div');
        col.classList.add('col');

        const card = document.createElement('div');
        card.classList.add('card', 'border-dark', 'mb-3', 'hover-effect');

        const cardBody = document.createElement('div');
        cardBody.classList.add('card-body', 'shadow');
        cardBody.innerHTML = `<h5 class="card-title">${feature.title}</h5><p class="card-text">${feature.text}</p>`;
        card.appendChild(cardBody);
        col.appendChild(card);
        featureContainer.appendChild(col);
      });

      // Footer
      const footer = document.querySelector('footer p');
      footer.textContent = data.footer.text;
    })
    .catch(error => console.error('Error loading the JSON data:', error));
});