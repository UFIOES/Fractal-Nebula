struct VERTEX_IN {
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

float4 main(VERTEX_IN input) : SV_TARGET {

	float4 output = input.color;

	return output;

}