---
+++
title = "Reporte"
draft = false
summary = ""
showSummary = false
+++
---
# Reporte: Implementación de Markdown, Git, GitHub, Hugo y GitHub Actions

**Autor:** Alexander Alcantar
**Materia:** Paradigmas de la programación 
**Fecha:** 2026  

---

# Introducción

El presente reporte documenta el proceso de aprendizaje e implementación de herramientas fundamentales en el desarrollo moderno de software. Durante las sesiones se trabajó con Markdown para documentación, Git para control de versiones, GitHub como plataforma en la nube, Hugo como generador de sitios estáticos y GitHub Actions para automatizar la publicación del sitio en GitHub Pages.

El objetivo principal fue construir el primer portafolio profesional utilizando herramientas reales del entorno de desarrollo actual.

---

# Primera Sesión: Markdown

## ¿Qué es Markdown?

Markdown es un lenguaje de marcado ligero diseñado para dar formato a texto de manera sencilla y legible. Permite estructurar documentos sin necesidad de escribir código HTML directamente.

Es ampliamente utilizado en documentación técnica, archivos README y sitios web estáticos.

## ¿Para qué sirve?

- Crear documentación técnica
- Redactar reportes
- Generar contenido web
- Escribir archivos README
- Crear blogs y portafolios

## Sintaxis básica de Markdown

### Encabezados

```markdown
# Encabezado nivel 1
## Encabezado nivel 2
### Encabezado nivel 3
```

### Negritas y cursivas

```markdown
**Texto en negritas**
*Texto en cursiva*
```

### Listas

Lista desordenada:

```markdown
- Elemento 1
- Elemento 2
- Elemento 3
```

Lista ordenada:

```markdown
1. Paso uno
2. Paso dos
3. Paso tres
```

### Enlaces

```markdown
[GitHub](https://github.com)
```

### Imágenes

```markdown
![Descripción](imagen.png)
```

### Código en línea

```markdown
`cout << "Hola Mundo";`
```

### Bloques de código

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Hola Mundo";
    return 0;
}
```

---

# Segunda Sesión: Git y GitHub

## ¿Qué es Git?

Git es un sistema de control de versiones distribuido creado en 2005. Permite registrar cambios en archivos y proyectos, facilitando el trabajo colaborativo y la administración de versiones.

### Ventajas de Git

- Historial completo de cambios
- Trabajo en ramas
- Recuperación de versiones anteriores
- Integración con plataformas en la nube

## Comandos esenciales de Git

Inicializar repositorio:

```bash
git init
```

Ver estado del repositorio:

```bash
git status
```

Agregar archivos:

```bash
git add .
```

Guardar cambios:

```bash
git commit -m "Mensaje descriptivo"
```

Crear rama:

```bash
git branch nombre-rama
```

Cambiar de rama:

```bash
git checkout nombre-rama
```

Conectar con repositorio remoto:

```bash
git remote add origin URL
```

Subir cambios:

```bash
git push -u origin main
```

Actualizar repositorio local:

```bash
git pull
```

---

## ¿Qué es GitHub?

GitHub es una plataforma de alojamiento de repositorios basada en Git. Permite almacenar proyectos en la nube y facilita la colaboración entre desarrolladores.

### Crear un repositorio en GitHub

1. Iniciar sesión.
2. Seleccionar “New repository”.
3. Asignar nombre al repositorio.
4. Crear repositorio.
5. Conectar el proyecto local con:
   
```bash
git remote add origin URL_DEL_REPOSITORIO
```

6. Subir archivos:

```bash
git push -u origin main
```

---

# Tercera Sesión: Hugo y GitHub Actions

## ¿Qué es Hugo?

Hugo es un generador de sitios web estáticos desarrollado en Go. Convierte archivos Markdown en páginas HTML optimizadas y listas para producción.

### Crear un sitio con Hugo

```bash
hugo new site mi-sitio
```

Entrar al directorio:

```bash
cd mi-sitio
```

Agregar un tema:

```bash
git submodule add URL_DEL_TEMA themes/tema
```

Crear contenido:

```bash
hugo new posts/primer-post.md
```

Generar el sitio:

```bash
hugo
```

Vista previa local:

```bash
hugo server
```

---

## ¿Qué es GitHub Actions?

GitHub Actions es una herramienta de automatización que permite ejecutar flujos de trabajo directamente desde un repositorio. Se utiliza para integración continua (CI) y despliegue continuo (CD).

En este proyecto se utilizó para automatizar la publicación del sitio en GitHub Pages.

---

## Publicar en GitHub Pages

1. Subir el proyecto a GitHub.
2. Crear carpeta:

```
.github/workflows
```

3. Crear archivo `hugo.yml` con la configuración del flujo de trabajo.
4. Activar GitHub Pages desde la configuración del repositorio.
5. Cada vez que se realice un `git push`, el sitio se actualizará automáticamente.



# Conversión a PDF

Para entregar el reporte se utilizó una extensión que convierte archivos Markdown a PDF. El archivo fuente `.md` se encuentra dentro del repositorio junto con todos los archivos del proyecto.

---

# Conclusión

Durante estas sesiones se integraron herramientas fundamentales del desarrollo moderno. Se aprendió a documentar con Markdown, controlar versiones con Git, trabajar en la nube con GitHub, generar sitios estáticos con Hugo y automatizar su publicación con GitHub Actions.

Este proyecto representa el inicio formal del portafolio profesional y establece una base sólida para futuros desarrollos académicos y profesionales.

---

# Portafolio

Repositorio en GitHub:  
[MI REPOSITORIO: ALXND3R](https://github.com/ALXND3R)

Página estática en GitHub Pages:  
[PAGINA](https://alxnd3r.github.io/PORTAFOLIO/)

---