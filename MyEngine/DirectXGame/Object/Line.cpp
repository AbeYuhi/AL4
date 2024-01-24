#include "Line.h"

Line::Line()
{
}

Line::~Line()
{
}

std::unique_ptr<Line> Line::Create() {
	std::unique_ptr<Line> object = std::make_unique<Line>();
	object->Initialize();

	return object;
}

void Line::Initialize() {
	//dxCommonのインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	//VertexResourceの生成
	vertexResource_ = CreateBufferResource(sizeof(VertexData) * kVertexNumber);

	//リソースの先頭のアドレスを使う
	vertexBufferView_.BufferLocation = vertexResource_->GetGPUVirtualAddress();
	vertexBufferView_.SizeInBytes = sizeof(VertexData) * kVertexNumber;
	vertexBufferView_.StrideInBytes = sizeof(VertexData);

	//Resourceにデータを書き込む
	vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));

	//奥
	vertexData_[0].position = { 0.0f, 0.0f, 0.0f, 1.0f }; //右下
	vertexData_[0].texcoord = { 0.0f, 1.0f };
	vertexData_[0].normal = { 0.0f, 0.0f, 1.0f };
	vertexData_[1].position = { 0.0f, 0.0f, 0.0f, 1.0f }; //右上
	vertexData_[1].texcoord = { 0.0f, 0.0f };
	vertexData_[1].normal = { 0.0f, 0.0f, 1.0f };

	renderItem_.Initialize();
}

void Line::Draw(LineInfo segment, Vector4 color) {
	TextureManager* textureManager = TextureManager::GetInstance();
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	GraphicsPipelineManager* psoManager = GraphicsPipelineManager::GetInstance();

	renderItem_.Update();

	vertexData_[0].position.x = segment.startPos.x;
	vertexData_[0].position.y = segment.startPos.y;
	vertexData_[0].position.z = segment.startPos.z;

	vertexData_[1].position.x = segment.endPos.x;
	vertexData_[1].position.y = segment.endPos.y;
	vertexData_[1].position.z = segment.endPos.z;

	//ViewPortの設定
	dxCommon->GetCommandList()->RSSetViewports(1, psoManager->GetViewPort());
	//Scirssorの設定
	dxCommon->GetCommandList()->RSSetScissorRects(1, psoManager->GetScissorRect());
	//パイプラインステートの設定
	dxCommon->GetCommandList()->SetPipelineState(psoManager->GetPSO());
	//ルートシグネチャの設定
	dxCommon->GetCommandList()->SetGraphicsRootSignature(psoManager->GetRootSignature());
	//プリミティブ形状を設定
	dxCommon->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
	//VBVの設定
	dxCommon->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView_);
	//マテリアルCBufferの場所を設定
	dxCommon->GetCommandList()->SetGraphicsRootConstantBufferView(0, renderItem_.materialInfo_.resource_->GetGPUVirtualAddress());
	//wvpCBufferの場所を設定
	dxCommon->GetCommandList()->SetGraphicsRootConstantBufferView(1, renderItem_.worldTransform_.resource_->GetGPUVirtualAddress());
	//SRVのDescriptorTableの先頭を設定、2はrootParameter[2]である
	dxCommon->GetCommandList()->SetGraphicsRootDescriptorTable(2, textureManager->GetTextureHandleGPU(1));
	//描画
	dxCommon->GetCommandList()->DrawInstanced(kVertexNumber, 1, 0, 0);
}