/*


  OK, ya ready for some fun? HTML + CSS styling + javascript all in and undebuggable environment

  one trick I've learned to how to debug HTML and CSS code.

  get all your HTML code (from html to /html) and past it into this test site
  muck with the HTML and CSS code until it's what you want
  https://www.w3schools.com/html/tryit.asp?filename=tryhtml_intro

  No clue how to debug javascrip other that write, compile, upload, refresh, guess, repeat

  I'm using class designators to set styles and id's for data updating
  for example:
  the CSS class .tabledata defines with the cell will look like
  <td><div class="tabledata" id = "switch"></div></td>

  the XML code will update the data where id = "switch"
  java script then uses getElementById
  document.getElementById("switch").innerHTML="Switch is OFF";


  .. now you can have the class define the look AND the class update the content, but you will then need
  a class for every data field that must be updated, here's what that will look like
  <td><div class="switch"></div></td>

  the XML code will update the data where class = "switch"
  java script then uses getElementsByClassName
  document.getElementsByClassName("switch")[0].style.color=text_color;


  the main general sections of a web page are the following and used here

  <html>
    <style>
    // dump CSS style stuff in here
    </style>
    <body>
      <header>
      // put header code for cute banners here
      </header>
      <main>
      // the buld of your web page contents
      </main>
      <footer>
      // put cute footer (c) 2021 xyz inc type thing
      </footer>
    </body>
    <script>
    // you java code between these tags
    </script>
  </html>


*/

// note R"KEYWORD( html page code )KEYWORD"; 
// again I hate strings, so char is it and this method let's us write naturally

const char PAGE_MAIN[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Plant Monitoring Dashboard</title>
</head>

<style>
    *,
    ::before,
    ::after {
        --tw-border-spacing-x: 0;
        --tw-border-spacing-y: 0;
        --tw-translate-x: 0;
        --tw-translate-y: 0;
        --tw-rotate: 0;
        --tw-skew-x: 0;
        --tw-skew-y: 0;
        --tw-scale-x: 1;
        --tw-scale-y: 1;
        --tw-pan-x: ;
        --tw-pan-y: ;
        --tw-pinch-zoom: ;
        --tw-scroll-snap-strictness: proximity;
        --tw-gradient-from-position: ;
        --tw-gradient-via-position: ;
        --tw-gradient-to-position: ;
        --tw-ordinal: ;
        --tw-slashed-zero: ;
        --tw-numeric-figure: ;
        --tw-numeric-spacing: ;
        --tw-numeric-fraction: ;
        --tw-ring-inset: ;
        --tw-ring-offset-width: 0px;
        --tw-ring-offset-color: #fff;
        --tw-ring-color: rgb(59 130 246 / 0.5);
        --tw-ring-offset-shadow: 0 0 #0000;
        --tw-ring-shadow: 0 0 #0000;
        --tw-shadow: 0 0 #0000;
        --tw-shadow-colored: 0 0 #0000;
        --tw-blur: ;
        --tw-brightness: ;
        --tw-contrast: ;
        --tw-grayscale: ;
        --tw-hue-rotate: ;
        --tw-invert: ;
        --tw-saturate: ;
        --tw-sepia: ;
        --tw-drop-shadow: ;
        --tw-backdrop-blur: ;
        --tw-backdrop-brightness: ;
        --tw-backdrop-contrast: ;
        --tw-backdrop-grayscale: ;
        --tw-backdrop-hue-rotate: ;
        --tw-backdrop-invert: ;
        --tw-backdrop-opacity: ;
        --tw-backdrop-saturate: ;
        --tw-backdrop-sepia: ;
        --tw-contain-size: ;
        --tw-contain-layout: ;
        --tw-contain-paint: ;
        --tw-contain-style: ;
    }

    ::backdrop {
        --tw-border-spacing-x: 0;
        --tw-border-spacing-y: 0;
        --tw-translate-x: 0;
        --tw-translate-y: 0;
        --tw-rotate: 0;
        --tw-skew-x: 0;
        --tw-skew-y: 0;
        --tw-scale-x: 1;
        --tw-scale-y: 1;
        --tw-pan-x: ;
        --tw-pan-y: ;
        --tw-pinch-zoom: ;
        --tw-scroll-snap-strictness: proximity;
        --tw-gradient-from-position: ;
        --tw-gradient-via-position: ;
        --tw-gradient-to-position: ;
        --tw-ordinal: ;
        --tw-slashed-zero: ;
        --tw-numeric-figure: ;
        --tw-numeric-spacing: ;
        --tw-numeric-fraction: ;
        --tw-ring-inset: ;
        --tw-ring-offset-width: 0px;
        --tw-ring-offset-color: #fff;
        --tw-ring-color: rgb(59 130 246 / 0.5);
        --tw-ring-offset-shadow: 0 0 #0000;
        --tw-ring-shadow: 0 0 #0000;
        --tw-shadow: 0 0 #0000;
        --tw-shadow-colored: 0 0 #0000;
        --tw-blur: ;
        --tw-brightness: ;
        --tw-contrast: ;
        --tw-grayscale: ;
        --tw-hue-rotate: ;
        --tw-invert: ;
        --tw-saturate: ;
        --tw-sepia: ;
        --tw-drop-shadow: ;
        --tw-backdrop-blur: ;
        --tw-backdrop-brightness: ;
        --tw-backdrop-contrast: ;
        --tw-backdrop-grayscale: ;
        --tw-backdrop-hue-rotate: ;
        --tw-backdrop-invert: ;
        --tw-backdrop-opacity: ;
        --tw-backdrop-saturate: ;
        --tw-backdrop-sepia: ;
        --tw-contain-size: ;
        --tw-contain-layout: ;
        --tw-contain-paint: ;
        --tw-contain-style: ;
    }

    /*
! tailwindcss v3.4.15 | MIT License | https://tailwindcss.com
*/

    /*
1. Prevent padding and border from affecting element width. (https://github.com/mozdevs/cssremedy/issues/4)
2. Allow adding a border to an element by just adding a border-width. (https://github.com/tailwindcss/tailwindcss/pull/116)
*/

    *,
    ::before,
    ::after {
        box-sizing: border-box;
        /* 1 */
        border-width: 0;
        /* 2 */
        border-style: solid;
        /* 2 */
        border-color: #e5e7eb;
        /* 2 */
    }

    ::before,
    ::after {
        --tw-content: '';
    }

    /*
1. Use a consistent sensible line-height in all browsers.
2. Prevent adjustments of font size after orientation changes in iOS.
3. Use a more readable tab size.
4. Use the user's configured `sans` font-family by default.
5. Use the user's configured `sans` font-feature-settings by default.
6. Use the user's configured `sans` font-variation-settings by default.
7. Disable tap highlights on iOS
*/

    html,
    :host {
        line-height: 1.5;
        /* 1 */
        -webkit-text-size-adjust: 100%;
        /* 2 */
        -moz-tab-size: 4;
        /* 3 */
        -o-tab-size: 4;
        tab-size: 4;
        /* 3 */
        font-family: ui-sans-serif, system-ui, sans-serif, "Apple Color Emoji", "Segoe UI Emoji", "Segoe UI Symbol", "Noto Color Emoji";
        /* 4 */
        font-feature-settings: normal;
        /* 5 */
        font-variation-settings: normal;
        /* 6 */
        -webkit-tap-highlight-color: transparent;
        /* 7 */
    }

    /*
1. Remove the margin in all browsers.
2. Inherit line-height from `html` so users can set them as a class directly on the `html` element.
*/

    body {
        margin: 0;
        /* 1 */
        line-height: inherit;
        /* 2 */
    }

    /*
1. Add the correct height in Firefox.
2. Correct the inheritance of border color in Firefox. (https://bugzilla.mozilla.org/show_bug.cgi?id=190655)
3. Ensure horizontal rules are visible by default.
*/

    hr {
        height: 0;
        /* 1 */
        color: inherit;
        /* 2 */
        border-top-width: 1px;
        /* 3 */
    }

    /*
Add the correct text decoration in Chrome, Edge, and Safari.
*/

    abbr:where([title]) {
        -webkit-text-decoration: underline dotted;
        text-decoration: underline dotted;
    }

    /*
Remove the default font size and weight for headings.
*/

    h1,
    h2,
    h3,
    h4,
    h5,
    h6 {
        font-size: inherit;
        font-weight: inherit;
    }

    /*
Reset links to optimize for opt-in styling instead of opt-out.
*/

    a {
        color: inherit;
        text-decoration: inherit;
    }

    /*
Add the correct font weight in Edge and Safari.
*/

    b,
    strong {
        font-weight: bolder;
    }

    /*
1. Use the user's configured `mono` font-family by default.
2. Use the user's configured `mono` font-feature-settings by default.
3. Use the user's configured `mono` font-variation-settings by default.
4. Correct the odd `em` font sizing in all browsers.
*/

    code,
    kbd,
    samp,
    pre {
        font-family: ui-monospace, SFMono-Regular, Menlo, Monaco, Consolas, "Liberation Mono", "Courier New", monospace;
        /* 1 */
        font-feature-settings: normal;
        /* 2 */
        font-variation-settings: normal;
        /* 3 */
        font-size: 1em;
        /* 4 */
    }

    /*
Add the correct font size in all browsers.
*/

    small {
        font-size: 80%;
    }

    /*
Prevent `sub` and `sup` elements from affecting the line height in all browsers.
*/

    sub,
    sup {
        font-size: 75%;
        line-height: 0;
        position: relative;
        vertical-align: baseline;
    }

    sub {
        bottom: -0.25em;
    }

    sup {
        top: -0.5em;
    }

    /*
1. Remove text indentation from table contents in Chrome and Safari. (https://bugs.chromium.org/p/chromium/issues/detail?id=999088, https://bugs.webkit.org/show_bug.cgi?id=201297)
2. Correct table border color inheritance in all Chrome and Safari. (https://bugs.chromium.org/p/chromium/issues/detail?id=935729, https://bugs.webkit.org/show_bug.cgi?id=195016)
3. Remove gaps between table borders by default.
*/

    table {
        text-indent: 0;
        /* 1 */
        border-color: inherit;
        /* 2 */
        border-collapse: collapse;
        /* 3 */
    }

    /*
1. Change the font styles in all browsers.
2. Remove the margin in Firefox and Safari.
3. Remove default padding in all browsers.
*/

    button,
    input,
    optgroup,
    select,
    textarea {
        font-family: inherit;
        /* 1 */
        font-feature-settings: inherit;
        /* 1 */
        font-variation-settings: inherit;
        /* 1 */
        font-size: 100%;
        /* 1 */
        font-weight: inherit;
        /* 1 */
        line-height: inherit;
        /* 1 */
        letter-spacing: inherit;
        /* 1 */
        color: inherit;
        /* 1 */
        margin: 0;
        /* 2 */
        padding: 0;
        /* 3 */
    }

    /*
Remove the inheritance of text transform in Edge and Firefox.
*/

    button,
    select {
        text-transform: none;
    }

    /*
1. Correct the inability to style clickable types in iOS and Safari.
2. Remove default button styles.
*/

    button,
    input:where([type='button']),
    input:where([type='reset']),
    input:where([type='submit']) {
        -webkit-appearance: button;
        /* 1 */
        background-color: transparent;
        /* 2 */
        background-image: none;
        /* 2 */
    }

    /*
Use the modern Firefox focus style for all focusable elements.
*/

    :-moz-focusring {
        outline: auto;
    }

    /*
Remove the additional `:invalid` styles in Firefox. (https://github.com/mozilla/gecko-dev/blob/2f9eacd9d3d995c937b4251a5557d95d494c9be1/layout/style/res/forms.css#L728-L737)
*/

    :-moz-ui-invalid {
        box-shadow: none;
    }

    /*
Add the correct vertical alignment in Chrome and Firefox.
*/

    progress {
        vertical-align: baseline;
    }

    /*
Correct the cursor style of increment and decrement buttons in Safari.
*/

    ::-webkit-inner-spin-button,
    ::-webkit-outer-spin-button {
        height: auto;
    }

    /*
1. Correct the odd appearance in Chrome and Safari.
2. Correct the outline style in Safari.
*/

    [type='search'] {
        -webkit-appearance: textfield;
        /* 1 */
        outline-offset: -2px;
        /* 2 */
    }

    /*
Remove the inner padding in Chrome and Safari on macOS.
*/

    ::-webkit-search-decoration {
        -webkit-appearance: none;
    }

    /*
1. Correct the inability to style clickable types in iOS and Safari.
2. Change font properties to `inherit` in Safari.
*/

    ::-webkit-file-upload-button {
        -webkit-appearance: button;
        /* 1 */
        font: inherit;
        /* 2 */
    }

    /*
Add the correct display in Chrome and Safari.
*/

    summary {
        display: list-item;
    }

    /*
Removes the default spacing and border for appropriate elements.
*/

    blockquote,
    dl,
    dd,
    h1,
    h2,
    h3,
    h4,
    h5,
    h6,
    hr,
    figure,
    p,
    pre {
        margin: 0;
    }

    fieldset {
        margin: 0;
        padding: 0;
    }

    legend {
        padding: 0;
    }

    ol,
    ul,
    menu {
        list-style: none;
        margin: 0;
        padding: 0;
    }

    /*
Reset default styling for dialogs.
*/

    dialog {
        padding: 0;
    }

    /*
Prevent resizing textareas horizontally by default.
*/

    textarea {
        resize: vertical;
    }

    /*
1. Reset the default placeholder opacity in Firefox. (https://github.com/tailwindlabs/tailwindcss/issues/3300)
2. Set the default placeholder color to the user's configured gray 400 color.
*/

    input::-moz-placeholder,
    textarea::-moz-placeholder {
        opacity: 1;
        /* 1 */
        color: #9ca3af;
        /* 2 */
    }

    input::placeholder,
    textarea::placeholder {
        opacity: 1;
        /* 1 */
        color: #9ca3af;
        /* 2 */
    }

    /*
Set the default cursor for buttons.
*/

    button,
    [role="button"] {
        cursor: pointer;
    }

    /*
Make sure disabled buttons don't get the pointer cursor.
*/

    :disabled {
        cursor: default;
    }

    /*
1. Make replaced elements `display: block` by default. (https://github.com/mozdevs/cssremedy/issues/14)
2. Add `vertical-align: middle` to align replaced elements more sensibly by default. (https://github.com/jensimmons/cssremedy/issues/14#issuecomment-634934210)
   This can trigger a poorly considered lint error in some tools but is included by design.
*/

    img,
    svg,
    video,
    canvas,
    audio,
    iframe,
    embed,
    object {
        display: block;
        /* 1 */
        vertical-align: middle;
        /* 2 */
    }

    /*
Constrain images and videos to the parent width and preserve their intrinsic aspect ratio. (https://github.com/mozdevs/cssremedy/issues/14)
*/

    img,
    video {
        max-width: 100%;
        height: auto;
    }

    /* Make elements with the HTML hidden attribute stay hidden by default */

    [hidden]:where(:not([hidden="until-found"])) {
        display: none;
    }

    .container {
        width: 100%;
    }

    @media (min-width: 640px) {
        .container {
            max-width: 640px;
        }
    }

    @media (min-width: 768px) {
        .container {
            max-width: 768px;
        }
    }

    @media (min-width: 1024px) {
        .container {
            max-width: 1024px;
        }
    }

    @media (min-width: 1280px) {
        .container {
            max-width: 1280px;
        }
    }

    @media (min-width: 1536px) {
        .container {
            max-width: 1536px;
        }
    }

    .visible {
        visibility: visible;
    }

    .collapse {
        visibility: collapse;
    }

    .fixed {
        position: fixed;
    }

    .relative {
        position: relative;
    }

    .sticky {
        position: sticky;
    }

    .top-0 {
        top: 0px;
    }

    .mx-auto {
        margin-left: auto;
        margin-right: auto;
    }

    .my-12 {
        margin-top: 3rem;
        margin-bottom: 3rem;
    }

    .mb-6 {
        margin-bottom: 1.5rem;
    }

    .mt-2 {
        margin-top: 0.5rem;
    }

    .mt-4 {
        margin-top: 1rem;
    }

    .mb-2 {
        margin-bottom: 0.5rem;
    }

    .block {
        display: block;
    }

    .inline {
        display: inline;
    }

    .flex {
        display: flex;
    }

    .inline-flex {
        display: inline-flex;
    }

    .table {
        display: table;
    }

    .contents {
        display: contents;
    }

    .hidden {
        display: none;
    }

    .w-2 {
        width: 0.5rem;
    }

    .w-2\/3 {
        width: 66.666667%;
    }

    .w-3 {
        width: 0.75rem;
    }

    .w-3\/5 {
        width: 60%;
    }

    .min-w-fit {
        min-width: -moz-fit-content;
        min-width: fit-content;
    }

    .max-w-4xl {
        max-width: 56rem;
    }

    .max-w-5xl {
        max-width: 64rem;
    }

    .max-w-fit {
        max-width: -moz-fit-content;
        max-width: fit-content;
    }

    .border-collapse {
        border-collapse: collapse;
    }

    .transform {
        transform: translate(var(--tw-translate-x), var(--tw-translate-y)) rotate(var(--tw-rotate)) skewX(var(--tw-skew-x)) skewY(var(--tw-skew-y)) scaleX(var(--tw-scale-x)) scaleY(var(--tw-scale-y));
    }

    .resize {
        resize: both;
    }

    .scroll-mt-20 {
        scroll-margin-top: 5rem;
    }

    .list-none {
        list-style-type: none;
    }

    .flex-row {
        flex-direction: row;
    }

    .flex-col {
        flex-direction: column;
    }

    .flex-wrap {
        flex-wrap: wrap;
    }

    .items-start {
        align-items: flex-start;
    }

    .items-center {
        align-items: center;
    }

    .justify-center {
        justify-content: center;
    }

    .justify-between {
        justify-content: space-between;
    }

    .justify-items-center {
        justify-items: center;
    }

    .gap-8 {
        gap: 2rem;
    }

    .gap-4 {
        gap: 1rem;
    }

    .gap-1 {
        gap: 0.25rem;
    }

    .gap-2 {
        gap: 0.5rem;
    }

    .self-center {
        align-self: center;
    }

    .rounded-3xl {
        border-radius: 1.5rem;
    }

    .rounded-full {
        border-radius: 9999px;
    }

    .border {
        border-width: 1px;
    }

    .bg-emerald-200 {
        --tw-bg-opacity: 1;
        background-color: rgb(167 243 208 / var(--tw-bg-opacity, 1));
    }

    .bg-emerald-50 {
        --tw-bg-opacity: 1;
        background-color: rgb(236 253 245 / var(--tw-bg-opacity, 1));
    }

    .bg-green-900 {
        --tw-bg-opacity: 1;
        background-color: rgb(20 83 45 / var(--tw-bg-opacity, 1));
    }

    .bg-white {
        --tw-bg-opacity: 1;
        background-color: rgb(255 255 255 / var(--tw-bg-opacity, 1));
    }

    .p-2 {
        padding: 0.5rem;
    }

    .p-3 {
        padding: 0.75rem;
    }

    .p-6 {
        padding: 1.5rem;
    }

    .p-8 {
        padding: 2rem;
    }

    .p-1 {
        padding: 0.25rem;
    }

    .px-4 {
        padding-left: 1rem;
        padding-right: 1rem;
    }

    .px-6 {
        padding-left: 1.5rem;
        padding-right: 1.5rem;
    }

    .py-6 {
        padding-top: 1.5rem;
        padding-bottom: 1.5rem;
    }

    .pb-3 {
        padding-bottom: 0.75rem;
    }

    .text-center {
        text-align: center;
    }

    .text-2xl {
        font-size: 1.5rem;
        line-height: 2rem;
    }

    .text-3xl {
        font-size: 1.875rem;
        line-height: 2.25rem;
    }

    .text-base {
        font-size: 1rem;
        line-height: 1.5rem;
    }

    .text-xl {
        font-size: 1.25rem;
        line-height: 1.75rem;
    }

    .font-bold {
        font-weight: 700;
    }

    .font-medium {
        font-weight: 500;
    }

    .font-semibold {
        font-weight: 600;
    }

    .text-black {
        --tw-text-opacity: 1;
        color: rgb(0 0 0 / var(--tw-text-opacity, 1));
    }

    .text-white {
        --tw-text-opacity: 1;
        color: rgb(255 255 255 / var(--tw-text-opacity, 1));
    }

    .underline {
        text-decoration-line: underline;
    }

    .accent-emerald-500 {
        accent-color: #10b981;
    }

    .shadow-xl {
        --tw-shadow: 0 20px 25px -5px rgb(0 0 0 / 0.1), 0 8px 10px -6px rgb(0 0 0 / 0.1);
        --tw-shadow-colored: 0 20px 25px -5px var(--tw-shadow-color), 0 8px 10px -6px var(--tw-shadow-color);
        box-shadow: var(--tw-ring-offset-shadow, 0 0 #0000), var(--tw-ring-shadow, 0 0 #0000), var(--tw-shadow);
    }

    .outline {
        outline-style: solid;
    }

    .filter {
        filter: var(--tw-blur) var(--tw-brightness) var(--tw-contrast) var(--tw-grayscale) var(--tw-hue-rotate) var(--tw-invert) var(--tw-saturate) var(--tw-sepia) var(--tw-drop-shadow);
    }

    .transition {
        transition-property: color, background-color, border-color, text-decoration-color, fill, stroke, opacity, box-shadow, transform, filter, -webkit-backdrop-filter;
        transition-property: color, background-color, border-color, text-decoration-color, fill, stroke, opacity, box-shadow, transform, filter, backdrop-filter;
        transition-property: color, background-color, border-color, text-decoration-color, fill, stroke, opacity, box-shadow, transform, filter, backdrop-filter, -webkit-backdrop-filter;
        transition-timing-function: cubic-bezier(0.4, 0, 0.2, 1);
        transition-duration: 150ms;
    }

    .ease-in-out {
        transition-timing-function: cubic-bezier(0.4, 0, 0.2, 1);
    }

    .hover\:bg-emerald-300:hover {
        --tw-bg-opacity: 1;
        background-color: rgb(110 231 183 / var(--tw-bg-opacity, 1));
    }

    .hover\:duration-300:hover {
        transition-duration: 300ms;
    }

    @media (min-width: 640px) {
        .sm\:w-2\/5 {
            width: 40%;
        }

        .sm\:max-w-\[18rem\] {
            max-width: 18rem;
        }

        .sm\:flex-row {
            flex-direction: row;
        }

        .sm\:items-start {
            align-items: flex-start;
        }
    }
</style>

<body class="bg-emerald-50">
    <header class="bg-green-900 text-white top-0 sticky">
        <section class="max-w-4xl flex mx-auto p-3 px-6 justify-center items-center">
            <h1 class="text-3xl font-roboto font-medium">
                <a href="#sensor">Plant Monitoring Dashboard</a>
            </h1>
        </section>
    </header>

    <main class="max-w-5xl mx-auto">
        <section id="settings" class="p-8 scroll-mt-20">
            <h2 class="text-3xl font-bold text-center mb-2 text-black ">Configurations</h2>
            <p class="text-center mb-2"><i>Note: An update rate of 0 means the sensor is disabled</i></p>
            <div class="flex flex-row justify-between">
                <div class="px-4"><b>Air Temperature</b> (update every: <span id="air-temp-slider">0</span> s):</div>

                <input type="range" min="0" max="3600" value="0" width="0%" oninput="updateAirTempSlider(this.value)"
                    class="px-4 w-3/5 accent-emerald-500" />
            </div>

            <div class="flex flex-row justify-between">
                <div class="px-4"><b>Soil Sensor</b> (update every: <span id="soil-slider">0</span> s):</div>

                <input type="range" min="0" max="3600" value="0" width="0%" oninput="updateSoilSlider(this.value)"
                    class="px-4 w-3/5 accent-emerald-500" />
            </div>

            <div class="flex flex-row justify-between">
                <div class="px-4"><b>Photocell Sensor</b> (update every: <span id="photocell-slider">0</span> s):</div>

                <input type="range" min="0" max="3600" value="0" width="0%" oninput="updatePhotocellSlider(this.value)"
                    class="px-4 w-3/5 accent-emerald-500" />
            </div>

            <div class="flex justify-center">
                <button type="button"
                    class="font-semibold text-base bg-emerald-200  hover:bg-emerald-300 transition hover:duration-300 ease-in-out inline-flex items-center rounded-full justify-center pb-3 p-2 px-6 min-w-fit max-w-fit mt-4 self-center"
                    id="config-btn" onclick="configBtnPress()">Save
                </button>
            </div>
        </section>

        <section id="sensor" class="p-6 scroll-mt-20">
            <h2 class="text-3xl font-bold text-center mb-6 text-black ">Sensor Readings</h2>
            <ul
                class="list-none mx-auto flex flex-col sm:flex-row flex-wrap justify-center items-center sm:items-start gap-8">

                <!-- Air Temperature -->
                <li class="w-2/3 sm:w-2/5 sm:max-w-[18rem] flex flex-col bg-white py-6 px-6 rounded-3xl shadow-xl">
                    <div class="flex justify-between">
                        <h3 class="mt-2 text-xl font-semibold">Air Temperature</h3>
                        <h3 class="text-2xl font-semibold">&#x1F321;</h3>

                    </div>

                    <div class="flex justify-between mt-2">
                        <span>
                            Current:
                        </span>
                        <span id="air-temp-f">
                            0
                        </span>
                        <span>
                            &deg;F
                        </span>
                    </div>

                    <button type="button"
                        class="font-semibold text-base bg-emerald-200  hover:bg-emerald-300 transition hover:duration-300 ease-in-out inline-flex items-center rounded-full justify-center pb-3 p-2 px-6 min-w-fit max-w-fit mt-4 self-center"
                        id="air-temp-btn" onclick="airTempBtnPress()">Update Now!
                    </button>

                </li>

                <!-- Moisture Sensor -->
                <li class="w-2/3 sm:w-2/5 sm:max-w-[18rem] flex flex-col bg-white py-6 px-6 rounded-3xl shadow-xl">
                    <div class="flex justify-between">
                        <h3 class="mt-2 text-xl font-semibold">Soil</h3>
                        <h3 class="text-3xl font-semibold">&#129716;</h3>

                    </div>

                    <div class="flex justify-between mt-2">
                        <span>
                            Moisture:
                        </span>
                        <span id="soil-moisture">
                            0
                        </span>
                        <span>
                            %
                        </span>
                    </div>

                    <div class="flex justify-between mt-2">
                        <span>
                            Temperature:
                        </span>
                        <span id="soil-temp-f">
                            0
                        </span>
                        <span>
                            &deg;F
                        </span>
                    </div>

                    <button type="button"
                        class="font-semibold text-base bg-emerald-200  hover:bg-emerald-300 transition hover:duration-300 ease-in-out inline-flex items-center rounded-full justify-center pb-3 p-2 px-6 min-w-fit max-w-fit mt-4 self-center"
                        id="soil-btn" onclick="soilBtnPress()">Update Now!
                    </button>

                </li>

                <!-- Photocell -->
                <li class="w-2/3 sm:w-2/5 sm:max-w-[18rem] flex flex-col bg-white py-6 px-6 rounded-3xl shadow-xl">
                    <div class="flex justify-between">
                        <h3 class="mt-2 text-xl font-semibold">Environment</h3>
                        <h3 class="text-2xl font-semibold">&#127763;</h3>

                    </div>
                    <div class="flex justify-between mt-2">
                        <span>
                            Current:
                        </span>
                        <span id="photocell">
                            Dark
                        </span>
                    </div>

                    <button type="button"
                        class="font-semibold text-base bg-emerald-200  hover:bg-emerald-300 transition hover:duration-300 ease-in-out inline-flex items-center rounded-full justify-center pb-3 p-2 px-6 min-w-fit max-w-fit mt-4 self-center"
                        id="photocell-btn" onclick="photocellBtnPress()">Update Now!
                    </button>
                </li>

                <!-- ir sensors -->
                <li class="w-2/3 sm:w-2/5 sm:max-w-[18rem] flex flex-col bg-white py-6 px-6 rounded-3xl shadow-xl">
                    <div class="flex justify-between">
                        <h3 class="mt-2 text-xl font-semibold">Intrusion Detection</h3>
                        <h3 class="text-2xl font-semibold">&#9888;</h3>

                    </div>
                    <div class="flex justify-between mt-2">
                        <span>
                            Current Status:
                        </span>
                        <span id="ir-sensor">
                            Clear
                        </span>
                    </div>
                </li>


                <!-- air quality sensor -->
                <li class="w-2/3 sm:w-2/5 sm:max-w-[18rem] flex flex-col bg-white py-6 px-6 rounded-3xl shadow-xl">
                    <div class="flex justify-between">
                        <h3 class="mt-2 text-xl font-semibold">Air Quality</h3>
                        <h3 class="text-2xl font-semibold">&#127811;</h3>

                    </div>
                    <div class="flex justify-between mt-2">
                        <span>
                            Air Quality Index:
                        </span>
                        <span id="air-quality-sensor">
                            0
                        </span>
                    </div>
                </li>

                <!-- humidity sensor -->
                <li class="w-2/3 sm:w-2/5 sm:max-w-[18rem] flex flex-col bg-white py-6 px-6 rounded-3xl shadow-xl">
                    <div class="flex justify-between">
                        <h3 class="mt-2 text-xl font-semibold">Humidity</h3>
                        <h3 class="text-2xl font-semibold">&#9729;</h3>

                    </div>
                    <div class="flex justify-between mt-2">
                        <span>
                            Current:
                        </span>
                        <span id="humidity-sensor">
                            0
                        </span>
                        <span>
                            %
                        </span>
                    </div>
                </li>

                <!-- sound sensor -->
                <li class="w-2/3 sm:w-2/5 sm:max-w-[18rem] flex flex-col bg-white py-6 px-6 rounded-3xl shadow-xl">
                    <div class="flex justify-between">
                        <h3 class="mt-2 text-xl font-semibold">Sound Detection</h3>
                        <h3 class="text-2xl font-semibold">&#128266;</h3>

                    </div>
                    <div class="flex justify-between mt-2">
                        <span>
                            Total noise detected:
                        </span>
                        <span id="sound-sensor">
                            0
                        </span>
                        <span>
                            times
                        </span>
                    </div>
                </li>

                <!-- smoke sensor -->
                <li class="w-2/3 sm:w-2/5 sm:max-w-[18rem] flex flex-col bg-white py-6 px-6 rounded-3xl shadow-xl">
                    <div class="flex justify-between">
                        <h3 class="mt-2 text-xl font-semibold">Smoke Detection</h3>
                        <h3 class="text-2xl font-semibold">&#128684;</h3>

                    </div>
                    <div class="flex justify-between mt-2">
                        <span>
                            Current Status
                        </span>
                        <span id="smoke-sensor">
                            Clear
                        </span>
                    </div>
                </li>

                <!-- flame sensor -->
                <li class="w-2/3 sm:w-2/5 sm:max-w-[18rem] flex flex-col bg-white py-6 px-6 rounded-3xl shadow-xl">
                    <div class="flex justify-between">
                        <h3 class="mt-2 text-xl font-semibold">Flame Detection</h3>
                        <h3 class="text-2xl font-semibold">&#128293;</h3>

                    </div>
                    <div class="flex justify-between mt-2">
                        <span>
                            Current Status
                        </span>
                        <span id="flame-sensor">
                            Clear
                        </span>
                    </div>
                </li>




                <!-- sensor list item template -->
                <!-- <li class="w-2/3 sm:w-2/5 sm:max-w-[18rem] flex flex-col bg-white py-6 px-6 rounded-3xl shadow-xl">
                    <div class="flex justify-between">
                        <h3 class="mt-2 text-xl font-semibold">Title</h3>
                        <h3 class="text-2xl font-semibold">Icon</h3>

                    </div>
                    <div class="flex justify-between mt-2">
                        <span>
                            Description:
                        </span>
                        <span id="id-name">
                            0
                        </span>
                        <span>
                            Unit
                        </span>
                    </div>

                    <button type="button"
                        class="font-semibold text-base bg-emerald-200  hover:bg-emerald-300 transition hover:duration-300 ease-in-out inline-flex items-center rounded-full justify-center pb-3 p-2 px-6 min-w-fit max-w-fit mt-4 self-center"
                        id="btn" onclick="ButtonPress1()">Update Now!
                    </button>
                </li> -->
            </ul>
        </section>

        <section id="status" class="p-6 my-12 scroll-mt-20">
            <h2 class="text-3xl font-bold text-center mb-6 text-black ">Commands</h2>
            <ul
                class="list-none mx-auto flex flex-col sm:flex-row flex-wrap justify-center items-center sm:items-start gap-8">

                <li class="w-2/3 sm:w-2/5 sm:max-w-[18rem] flex flex-col bg-white py-6 px-6 rounded-3xl shadow-xl">
                    <div class="flex justify-between">
                        <h3 class="mt-2 text-xl font-semibold">Watering</h3>
                        <h3 class="text-2xl font-semibold">&#128167;</h3>

                    </div>
                    <div class="flex justify-between mt-2">
                        <span>
                            Turn on water pump for 5s
                        </span>
                    </div>

                    <button type="button"
                        class="font-semibold text-base bg-emerald-200  hover:bg-emerald-300 transition hover:duration-300 ease-in-out inline-flex items-center rounded-full justify-center pb-3 p-2 px-6 min-w-fit max-w-fit mt-4 self-center"
                        id="watering-btn" onclick="wateringBtnPress()">Water Now!
                    </button>
                </li>

                <li class="w-2/3 sm:w-2/5 sm:max-w-[18rem] flex flex-col bg-white py-6 px-6 rounded-3xl shadow-xl">
                    <div class="flex justify-between">
                        <h3 class="mt-2 text-xl font-semibold">LED Grow Light</h3>
                        <h3 class="text-2xl font-semibold">&#128161;</h3>

                    </div>
                    <div class="flex justify-between mt-2">
                        <span>
                            Current:
                        </span>
                        <span id="grow-light">
                            Off
                        </span>
                    </div>

                    <button type="button"
                        class="font-semibold text-base bg-emerald-200  hover:bg-emerald-300 transition hover:duration-300 ease-in-out inline-flex items-center rounded-full justify-center pb-3 p-2 px-6 min-w-fit max-w-fit mt-4 self-center"
                        id="grow-light-btn" onclick="growLightBtnPress()">Toggle
                    </button>
                </li>

                <li class="w-2/3 sm:w-2/5 sm:max-w-[18rem] flex flex-col bg-white py-6 px-6 rounded-3xl shadow-xl">
                    <div class="flex justify-between">
                        <h3 class="mt-2 text-xl font-semibold">LED Brightness</h3>
                        <h3 class="text-2xl font-semibold">&#128161;</h3>

                    </div>
                    <div class="flex justify-between mt-2">
                        <span>
                            Current:
                        </span>
                        <span id="brightness-light">
                            Bright
                        </span>
                    </div>

                    <button type="button"
                        class="font-semibold text-base bg-emerald-200  hover:bg-emerald-300 transition hover:duration-300 ease-in-out inline-flex items-center rounded-full justify-center pb-3 p-2 px-6 min-w-fit max-w-fit mt-4 self-center"
                        id="brightness-btn" onclick="lightBrightnessBtnPress()">Toggle
                    </button>
                </li>

                <li class="w-2/3 sm:w-2/5 sm:max-w-[18rem] flex flex-col bg-white py-6 px-6 rounded-3xl shadow-xl">
                    <div class="flex justify-between">
                        <h3 class="mt-2 text-xl font-semibold">LED Color</h3>
                        <h3 class="text-2xl font-semibold">&#128161;</h3>

                    </div>
                    <div class="flex justify-between mt-2">
                        <span>
                            Current Color:
                        </span>
                        <span id="light-color">
                            RGB
                        </span>
                    </div>

                    <div class="flex justify-center flex-wrap gap-2">
                        <button type="button"
                            class="font-semibold text-base bg-emerald-200  hover:bg-emerald-300 transition hover:duration-300 ease-in-out inline-flex items-center rounded-full justify-center pb-3 p-2 px-6 min-w-fit max-w-fit mt-2 self-center"
                            id="red-btn" onclick="lightRedBtnPress()">Red
                        </button>

                        <button type="button"
                            class="font-semibold text-base bg-emerald-200  hover:bg-emerald-300 transition hover:duration-300 ease-in-out inline-flex items-center rounded-full justify-center pb-3 p-2 px-6 min-w-fit max-w-fit mt-2 self-center"
                            id="green-btn" onclick="lightGreenBtnPress()">Green
                        </button>

                        <button type="button"
                            class="font-semibold text-base bg-emerald-200  hover:bg-emerald-300 transition hover:duration-300 ease-in-out inline-flex items-center rounded-full justify-center pb-3 p-2 px-6 min-w-fit max-w-fit mt-2 self-center"
                            id="blue-btn" onclick="lightBlueBtnPress()">Blue
                        </button>

                        <button type="button"
                            class="font-semibold text-base bg-emerald-200  hover:bg-emerald-300 transition hover:duration-300 ease-in-out inline-flex items-center rounded-full justify-center pb-3 p-2 px-6 min-w-fit max-w-fit mt-2 self-center"
                            id="rgb-btn" onclick="rgbBtnPress()">Blinking RGB
                        </button>
                    </div>

                </li>

                <li class="w-2/3 sm:w-2/5 sm:max-w-[18rem] flex flex-col bg-white py-6 px-6 rounded-3xl shadow-xl">
                    <div class="flex justify-between">
                        <h3 class="mt-2 text-xl font-semibold">Buzzer</h3>
                        <h3 class="text-2xl font-semibold">&#128276;</h3>

                    </div>
                    <div class="flex justify-between mt-2">
                        <span>
                            Turn on warning buzzer for 2s
                        </span>
                    </div>

                    <button type="button"
                        class="font-semibold text-base bg-emerald-200  hover:bg-emerald-300 transition hover:duration-300 ease-in-out inline-flex items-center rounded-full justify-center pb-3 p-2 px-6 min-w-fit max-w-fit mt-4 self-center"
                        id="buzzer-btn" onclick="buzzerBtnPress()">Beep Now!
                    </button>
                </li>

                <li class="w-2/3 sm:w-2/5 sm:max-w-[18rem] flex flex-col bg-white py-6 px-6 rounded-3xl shadow-xl">
                    <div class="flex justify-between">
                        <h3 class="mt-2 text-xl font-semibold">Display</h3>
                        <h3 class="text-2xl font-semibold">&#128223;</h3>

                    </div>
                    <div class="flex justify-between mt-2">
                        <span>
                            Write a system-generated message to the display or clear it
                        </span>
                    </div>

                    <div class="flex justify-center flex-wrap gap-2">
                        <button type="button"
                            class="font-semibold text-base bg-emerald-200  hover:bg-emerald-300 transition hover:duration-300 ease-in-out inline-flex items-center rounded-full justify-center pb-3 p-2 px-6 min-w-fit max-w-fit mt-4 self-center"
                            id="display-write-btn" onclick="writeBtnPress()">Write
                        </button>

                        <button type="button"
                            class="font-semibold text-base bg-emerald-200  hover:bg-emerald-300 transition hover:duration-300 ease-in-out inline-flex items-center rounded-full justify-center pb-3 p-2 px-6 min-w-fit max-w-fit mt-4 self-center"
                            id="display-clear-btn" onclick="clearBtnPress()">Clear
                        </button>
                    </div>
                </li>
            </ul>
        </section>
    </main>
</body>

<script>
    // global variable visible to all javascript functions
    var xmlHttp = createXmlHttpObject();

    // var save the config values (not sent yet)
    var airTempRate = 1;
    var soilRate = 1;
    var photocellRate = 1;

    // function to create XML object
    function createXmlHttpObject() {
        if (window.XMLHttpRequest) {
            xmlHttp = new XMLHttpRequest();
        } else {
            xmlHttp = new ActiveXObject("Microsoft.XMLHTTP");
        }
        return xmlHttp;
    }

    // function to handle button press from HTML code above
    // and send a processing string back to server
    // this processing string is use in the .on method
    function configBtnPress() {
        var xhttp = new XMLHttpRequest();
        var message;
        // if you want to handle an immediate reply (like status from the ESP)
        // handling of the button press use this code
        // since this button status from the ESP is in the main XML code
        // we don't need this
        // remember that if you want immediate processing feedback you must send it
        // in the ESP handling function and here
        /*
          xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
              message = this.responseText;
              // update some HTML data
            }
          }
          */

        // NOTE: whatever you name the server.on "/name" is
        // you need to put the "name" in 2nd arg of open below

        // NOTE: ? is a delimiter
        // first arg config is use in the .on method
        // server.on("/config", updateConfig);
        // then the second arg VALUE is use in the processing function
        // String t_state = server.arg("VALUE");
        // then + the configs value property
        xhttp.open(
            "PUT",
            "/config?airTempRate=" +
            airTempRate +
            "&soilRate=" +
            soilRate +
            "&photocellRate=" +
            photocellRate,
            true
        );
        xhttp.send();
    }

    // TODO: finish the following methods
    function airTempBtnPress() {
        var xhttp = new XMLHttpRequest();

        // get immediate feedback & update sensor
        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("air-temp-f").innerHTML = this.responseText
            }
        }

        xhttp.open("PUT", "/airTempBtn", false);
        xhttp.send();
    }

    function soilBtnPress() {
        var xhttp = new XMLHttpRequest();

        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                // moisture + temp response
                let xml = this.responseXML;
                let moisture = xml.getElementsByTagName("moisture")[0].textContent;
                let temp = xml.getElementsByTagName("temp")[0].textContent;

                document.getElementById("soil-moisture").innerHTML = moisture;
                document.getElementById("soil-temp-f").innerHTML = temp;
            }
        }

        xhttp.open("PUT", "/soilBtn", false);
        xhttp.send();
    }

    function photocellBtnPress() {
        var xhttp = new XMLHttpRequest();

        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("photocell").innerHTML = this.responseText
            }
        }

        xhttp.open("PUT", "/photocellBtn", false);
        xhttp.send();
    }

    function wateringBtnPress() {
        var xhttp = new XMLHttpRequest();

        xhttp.open("PUT", "/waterBtn", false);
        xhttp.send();
    }

    function growLightBtnPress() {
        var xhttp = new XMLHttpRequest();

        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("grow-light").innerHTML = this.responseText
            }
        }

        xhttp.open("PUT", "/growLightBtn", false);
        xhttp.send();
    }

    function lightBrightnessBtnPress() {
        var xhttp = new XMLHttpRequest();

        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("brightness-lightt").innerHTML = this.responseText
            }
        }

        xhttp.open("PUT", "/brightnessBtn", false);
        xhttp.send();
    }

    function lightRedBtnPress() {
        var xhttp = new XMLHttpRequest();

        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("light-color").innerHTML = this.responseText
            }
        }

        xhttp.open("PUT", "/redBtn", false);
        xhttp.send();
    }

    function lightGreenBtnPress() {
        var xhttp = new XMLHttpRequest();

        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("light-color").innerHTML = this.responseText
            }
        }

        xhttp.open("PUT", "/greenBtn", false);
        xhttp.send();
    }

    function lightBlueBtnPress() {
        var xhttp = new XMLHttpRequest();

        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("light-color").innerHTML = this.responseText
            }
        }

        xhttp.open("PUT", "/blueBtn", false);
        xhttp.send();
    }

    function rgbBtnPress() {
        var xhttp = new XMLHttpRequest();

        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("light-color").innerHTML = this.responseText
            }
        }

        xhttp.open("PUT", "/rgbBtn", false);
        xhttp.send();
    }

    function buzzerBtnPress() {
        var xhttp = new XMLHttpRequest();

        xhttp.open("PUT", "/buzzerBtn", false);
        xhttp.send();
    }

    function writeBtnPress() {
        var xhttp = new XMLHttpRequest();

        xhttp.open("PUT", "/writeBtn", false);
        xhttp.send();
    }

    function clearBtnPress() {
        var xhttp = new XMLHttpRequest();

        xhttp.open("PUT", "/clearBtn", false);
        xhttp.send();
    }

    function updateAirTempSlider(value) {
        airTempRate = value;
        document.getElementById("air-temp-slider").innerHTML = value;
    }

    function updateSoilSlider(value) {
        soilRate = value;
        document.getElementById("soil-slider").innerHTML = value;
    }

    function updatePhotocellSlider(value) {
        photocellRate = value;
        document.getElementById("photocell-slider").innerHTML = value;
    }

    // function to handle the response from the ESP
    // TODO: complete this. 349
    function response() { }

    // general processing code for the web page to ask for an XML stream
    // this is actually why you need to keep sending data to the page to
    // force this call with stuff like this
    // server.on("/xml", SendXML);
    // otherwise the page will not request XML from the ESP,
    // and updates will not happen
    function process() {
        if (xmlHttp.readyState == 0 || xmlHttp.readyState == 4) {
            xmlHttp.open("PUT", "xml", true);
            xmlHttp.onreadystatechange = response;
            xmlHttp.send(null);
        }
        // you may have to play with this value, big pages need more porcessing time,
        // and hence, a longer timeout
        setTimeout("process()", 100);
    }

</script>

</html>



)=====";
