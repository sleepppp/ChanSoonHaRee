#include "stdafx.h"
#include "LightSystem.h"

#include "RenderTargetBuffer.h"
#include "Shader.h"
#include "PointLight.h"


/*********************************************************************************************
## LightSystem ##
***********************************************************************************************/
LightSystem::LightSystem()
{
	//������ ��� �� ������ ����Ÿ��
	renderTargetBuffer = new RenderTargetBuffer(WinSizeX, WinSizeY, DXGI_FORMAT_R16G16B16A16_FLOAT);
	renderTargetBuffer->Create();
	//�� ������ ����� ī�� �� ����
	copyResource = new RenderTargetBuffer(WinSizeX, WinSizeY, DXGI_FORMAT_R8G8B8A8_UNORM);
	copyResource->Create();
	//���̴� ����
	lightingShader = new Shader(L"Lighting.hlsl");
	deferredShader = new Shader(L"Deferred.hlsl");
	//��� ���� ����
	sunBuffer = new SunLightBuffer;
	pointLightBuffer = new PointLightBuffer;
	//�̸� �ִ� ������ �� ��ŭ ���� �Ҵ�
	pointLightList.reserve(_MaxPointLight);

	this->CreateTable();
	state = State::Default;
	//this->ChangeState(State::Afternoon);
}

/*********************************************************************************************
## ~LightSystem ##
***********************************************************************************************/
LightSystem::~LightSystem()
{
	pointLightList.clear();

	SafeDelete(pointLightBuffer);
	SafeDelete(sunBuffer);

	SafeDelete(deferredShader);
	SafeDelete(lightingShader);

	SafeDelete(copyResource);
	SafeDelete(renderTargetBuffer);
}

/*********************************************************************************************
## BeginLighting ##
***********************************************************************************************/
void LightSystem::BeginLighting()
{
	//ȭ�� �������� ����Ʈ��� ������۸� ����
	pointLightBuffer->data.lightSize = this->pointLightList.size();
	for (UINT i = 0; i < pointLightList.size(); ++i)
	{
		pointLightBuffer->data.lightList[i].lightColor = pointLightList[i]->GetColor();
		pointLightBuffer->data.lightList[i].origin = _Camera->GetRelativeVector2(pointLightList[i]->GetPosition());
		pointLightBuffer->data.lightList[i].originRange = pointLightList[i]->GetOriginRange() * _Camera->GetZoom();
		pointLightBuffer->data.lightList[i].intensity = pointLightList[i]->GetIntensity();
	}

	//D2D������ �� ����ü�� ����Ÿ�� ���ε� ����
	//����Ÿ���� �ڿ��� ������ �ϼ��ɷ��� ���ε��� ������ �־�� �Ѵ�. 
	_D2DRenderTarget->EndDraw();
	this->renderTargetBuffer->BindRenderTarget();
	//D2D�� �׷��� ����� SRV���� ���ۿ� ī��(����ü�ο� ���� �ִ� �ڿ��� SRV�� ����� �� ���� ������ �ʼ� �Ұ����ϰ� �� ����� ä��)
	_D3DDeviceContext->CopyResource(this->copyResource->GetTexture2D(), _DXRenderer->GetBackBufferTexture2d());
}
/*********************************************************************************************
## Lighting ##
***********************************************************************************************/
void LightSystem::Lighting()
{
	//ȭ��ũ���� ��鸸�� �׷��� ���̱� ������ �������� �� �ε��� ���۴� �ʿ����. 
	_D3DDeviceContext->IASetInputLayout(nullptr);
	_D3DDeviceContext->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);
	_D3DDeviceContext->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
	_D3DDeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	{
		//SRV�� �������,���̴� ���ε�
		_D3DDeviceContext->PSSetShaderResources(0, 1, copyResource->GetLPSRV());
		sunBuffer->SetPSBuffer(0);
		pointLightBuffer->SetPSBuffer(1);
		lightingShader->Render();
	}
	//������
	_D3DDeviceContext->Draw(4, 0);
}
/*********************************************************************************************
## EndLighting ##
***********************************************************************************************/
void LightSystem::EndLighting()
{
	//����ü�ο� ���� �ִ� ����Ÿ�� �ٽ� ���ε�
	_DXRenderer->BindSwapChainRenderTarget();
	//ȭ��ũ���� ��鸸�� �׷��� ���̱� ������ �������� �� �ε��� ���۴� �ʿ����. 
	_D3DDeviceContext->IASetInputLayout(nullptr);
	_D3DDeviceContext->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);
	_D3DDeviceContext->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
	_D3DDeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	{
		//������ ��� ����,���̴� ���ε�
		_D3DDeviceContext->PSSetShaderResources(1, 1, renderTargetBuffer->GetLPSRV());
		deferredShader->Render();
	}
	//������
	_D3DDeviceContext->Draw(4, 0);
	//�������� �������Ƿ� ����Ʈ ����Ʈ�� ���� 
	pointLightList.clear();
	//UI�������ؾ� �ϹǷ� D2D������ ����
	_D2DRenderTarget->BeginDraw();
}
/*********************************************************************************************
## OnGui ##
***********************************************************************************************/
void LightSystem::OnGui()
{
	ImGui::Begin("LightSystem");
	{
		ImGui::SliderFloat("WorldAmbient", &sunBuffer->data.worldAmbient, 0.f, 1.f);
		ImGui::SliderFloat("SunIntensity", &sunBuffer->data.sunIntensity, 0.f, 1.f);
		ImGui::ColorEdit4("SunColor", &sunBuffer->data.sunColor.r,
			ImGuiColorEditFlags_Float | ImGuiColorEditFlags_AlphaPreviewHalf);
		ImGui::End();
	}

}
/*********************************************************************************************
## RequestLighting ##
***********************************************************************************************/
void LightSystem::RequestLighting(PointLight * light)
{
	pointLightList.push_back(light);
}

void LightSystem::CreateTable()
{
	SunLightBuffer::BufferData afternoonData;
	afternoonData.sunColor = GameColor(1.f, 1.f, 1.f, 1.f);
	afternoonData.sunIntensity = 0.5f;
	afternoonData.worldAmbient = 0.5f;
	sunDataTable.insert(make_pair(State::Afternoon, afternoonData));

	SunLightBuffer::BufferData eveningData;
	eveningData.sunColor = GameColor(1.f, 0.6f,0.137f, 1.f);
	eveningData.sunIntensity = 0.8f;
	eveningData.worldAmbient = 0.3f;
	sunDataTable.insert(make_pair(State::Evening, eveningData));

	SunLightBuffer::BufferData nightData;
	nightData.sunColor = GameColor(0.06f, 0.155f, 0.675f, 1.f);
	nightData.sunIntensity = 0.744f;
	nightData.worldAmbient = 0.135f;
	sunDataTable.insert(make_pair(State::Night, nightData));
}

void LightSystem::ChangeState(State state)
{
	this->state = state;
	DataTableIter iter = sunDataTable.find(state);
	if (iter != sunDataTable.end())
	{
		sunBuffer->data = iter->second;
	}
}

