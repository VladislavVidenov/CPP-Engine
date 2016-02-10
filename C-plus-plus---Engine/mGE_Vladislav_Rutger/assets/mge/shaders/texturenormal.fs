//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1


uniform sampler2D matDiffuse;
uniform sampler2D normalMap;
uniform vec3 cameraPosition;
uniform vec3 lightPosition;


in vec3 vertices;
in vec2 uvs;
in mat3 TBN;

out vec4 fragment_color;
//vec3 CalcBumpNormal(){
//    vec3 Normal = vec3(normals);
//    vec3 Tangent = vec3(wTangent);
//    Tangent = normalize(Tangent - dot(Tangent, Normal) * Normal);
//    vec3 Bitangent = cross(Tangent, Normal);
//    vec3 BumpMapNormal = texture(normalMap, uvs).rgb;
//    BumpMapNormal = normalize(BumpMapNormal * 2.0 - 1.0);
//    mat3 TBN = mat3(Tangent, Bitangent, Normal);
//    vec3 NewNormal = normalize(TBN * BumpMapNormal);
//    return NewNormal;
//}
void main( void )
{


    vec3 normal = texture(normalMap, uvs).rgb;
    normal = normalize(normal * 2.0 - 1.0);
    normal = normalize(TBN * normal);


    vec3 color = texture(matDiffuse, uvs).rgb;
    vec3 ambient = 0.1 * color;

    vec3 lightDir = normalize(lightPosition - vertices);
    float diff = max(dot(lightDir, normal), 0.0f);
    vec3 diffuse = diff * color;
    // Specular
    vec3 viewDir = normalize(cameraPosition - vertices);

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0f), 32.0f);
    vec3 specular = vec3(0.2f) * spec;

    fragment_color = vec4(ambient + diffuse + specular, 1.0f);


    //fragment_color = vec4(normal,1.f);

 //   normalizedNormal = texture(normalMap, uvs).rgb;
  //  normalizedNormal = normalize(normalizedNormal * 2.0 - 1.0);

   // vec3 viewDirection = normalize(cameraPosition - vertices);


   // vec3 finalColor;
   // finalColor = getDirectionalLight(dirLight,normalizedNormal,viewDirection);

//    for(int i = 0; i < lightNumber; i++)
//    {
//        finalColor += getPointLight(pointLight[i],normalizedNormal,vertices,viewDirection);
//    }
 //   fragment_color = vec4(finalColor, 1.f);
}
//vec3 getDirectionalLight(DirLight light, vec3 n, vec3 viewDirection)
//{
//    vec3 lightDirection = normalize(-light.direction);
//
//    float diffuse = max(dot(n,lightDirection),0.f);
//
//    vec3 reflectDirection = reflect(-lightDirection, n);
//    float specular = pow(max(dot(viewDirection, reflectDirection),0.f),material.shininess);
//
//    vec3 ambientTerm = light.ambient * vec3(texture(matDiffuse, uvs));
//    vec3 diffuseTerm = light.diffuse * diffuse * vec3(texture(matDiffuse, uvs));
//    vec3 specularTerm = light.specular * specular * material.specular;
//
//    return (ambientTerm + diffuseTerm + specularTerm);
//}
//vec3 getPointLight(PointLight light, vec3 n, vec3 vertpos, vec3 viewDirection)
//{
//    if(light.constant == 0) return vec3(0,0,0);
//    //ambient
//    vec3 ambientTerm = light.ambient * vec3(texture(matDiffuse, uvs));
//
//    vec3 lightDirection = normalize(light.position - vertpos);
//    //diffuse
//    float diffuse = max(dot(n, lightDirection),0.0f);
//    vec3 diffuseTerm = light.diffuse * diffuse * vec3(texture(matDiffuse, uvs));
//
//    //specular - BLINN - PHONG
//   vec3 halfWayDir = normalize(lightDirection + viewDirection);
//   float specular = pow(max(dot(n, halfWayDir), 0.f), material.shininess);
//   //specular - BLINN
//   // vec3 reflectDirection = reflect(-lightDirection, n);
//   // float specular = pow(max(dot(reflectDirection, viewDirection), 0.f), material.shininess);
//    vec3 specularTerm = light.specular * specular * material.specular;
//    //Attenuation
//    float distance = length(light.position - vertpos);
//    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
//
//    ambientTerm *= attenuation;
//    diffuseTerm *= attenuation;
//    specularTerm *= attenuation;
//
//    return (ambientTerm + diffuseTerm + specularTerm);
//}
