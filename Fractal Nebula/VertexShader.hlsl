cbuffer matrixBuffer : register(b0) {
	matrix world;
	matrix view;
	matrix projection;
};

struct VERTEX_IN {
	float4 position : POSITION;
	float4 color : COLOR;
};

struct VERTEX_OUT {
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

VERTEX_OUT main(VERTEX_IN input) {

	VERTEX_OUT output;

	input.position.w = 1.0f;

	output.position = input.position;

	output.position = mul(output.position, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);

	output.color = input.color;

	return output;

}