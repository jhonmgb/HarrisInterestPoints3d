// DISCLAIMER: This Shader program has been extracted from
// the Hello GL2 Example inclued in the Qt 5.11.2 package.
// For more information: http://doc.qt.io/qt-5/qtopengl-hellogl2-example.html

varying highp vec3 vert;
varying highp vec3 vertNormal;
uniform highp vec3 lightPos;
uniform highp vec3 currentColor;

void main()
{
    highp vec3 L = normalize(lightPos - vert);
    highp float NL = max(dot(normalize(vertNormal), L), 0.0);
    highp vec3 color = currentColor;
    highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);
    gl_FragColor = vec4(col, 1.0);
}
