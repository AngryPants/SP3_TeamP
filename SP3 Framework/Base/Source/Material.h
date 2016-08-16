#ifndef MATERIAL_H
#define MATERIAL_H

struct MaterialComponent {

public:
	//Variable(s)
	float r, g, b;

	//Constructor(s) & Destructor
	MaterialComponent(float r = 0.1f, float g = 0.1f, float b = 0.1f) {
		Set(r, g, b);
	}
	~MaterialComponent() {}

	//Setter(s)
	void Set(float r, float g, float b) {
		this->r = r; this->g = g; this->b = b;
	}

};

struct Material {

public:
	//Variable(s)
	MaterialComponent kAmbient;
	MaterialComponent kDiffuse;
	MaterialComponent kSpecular;
	float kShininess;

	//Constructor(s) & Destructor
	Material() {

		kAmbient.Set(0.1f, 0.1f, 0.1f);
		kDiffuse.Set(0.6f, 0.6f, 0.6f);
		kSpecular.Set(0.1f, 0.1f, 0.1f);
		kShininess = 5.0f;

	}
	~Material() {}

};

#endif