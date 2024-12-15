document.addEventListener('DOMContentLoaded', function () {
    fetch('./scriptHome.json')
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
  
        // Card
        const cardHeader = document.querySelector('.card-header');
        cardHeader.textContent = data.card.header;
        const cardBody = document.querySelector('.card-body');
        cardBody.querySelector('.card-text').textContent = data.card.body;
  
        // Sections
        const sectionContainer = document.querySelector('.row');
        data.sections.forEach(section => {
          const colDiv = document.createElement('div');
          colDiv.classList.add('col');
          const cardDiv = document.createElement('div');
          cardDiv.classList.add('card', 'shadow');
          const img = document.createElement('img');
          img.classList.add('card-img-top');
          img.src = section.image;
          img.alt = section.title;
          const cardBodyDiv = document.createElement('div');
          cardBodyDiv.classList.add('card-body');
          const cardTitle = document.createElement('h5');
          cardTitle.classList.add('card-title');
          cardTitle.textContent = section.title;
          const cardText = document.createElement('p');
          cardText.classList.add('card-text');
          cardText.textContent = section.description;
          const buttonDiv = document.createElement('div');
          buttonDiv.classList.add('d-flex', 'justify-content-end');
          const button = document.createElement('a');
          button.classList.add('btn', 'btn-primary', 'hover-effect', 'shadow');
          button.style.backgroundColor = 'green';
          button.href = section.link;
          button.textContent = 'Vai alla pagina';
          buttonDiv.appendChild(button);
          cardBodyDiv.appendChild(cardTitle);
          cardBodyDiv.appendChild(cardText);
          cardBodyDiv.appendChild(buttonDiv);
          cardDiv.appendChild(img);
          cardDiv.appendChild(cardBodyDiv);
          colDiv.appendChild(cardDiv);
          sectionContainer.appendChild(colDiv);
        });
  
        // Footer
        const footerText = document.querySelector('footer p');
        footerText.textContent = data.footer.text;        
      })
      .catch(error => console.error('Error loading JSON data:', error));
  });
  