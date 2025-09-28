#pragma once
#include "ScoreContext.h"
#include "ScoreEditorTimeline.h"
#include "Rendering/Framebuffer.h"
#include "Rendering/Renderer.h"

namespace MikuMikuWorld
{
	namespace Engine
	{
		struct DrawingParticle;
	}

	enum class ParticleEffectType : uint32_t;

	class ScorePreviewBackground
	{
		std::string backgroundFile;
		std::string jacketFile;
		Framebuffer frameBuffer;
		float brightness;
		bool init;
		
		struct DefaultJacket
		{
			static std::array<DirectX::XMFLOAT4, 4> getLeftUV();
			static std::array<DirectX::XMFLOAT4, 4> getRightUV();
			static std::array<DirectX::XMFLOAT4, 4> getLeftMirrorUV();
			static std::array<DirectX::XMFLOAT4, 4> getRightMirrorUV();
			static std::array<DirectX::XMFLOAT4, 4> getCenterUV();
			static std::array<DirectX::XMFLOAT4, 4> getMirrorCenterUV();
		};
		void updateDrawDefaultJacket(Renderer* renderer, const Jacket& jacket);
		public:
		ScorePreviewBackground();
		~ScorePreviewBackground();

		void setBrightness(float value);
		void update(Renderer* renderer, const Jacket& jacket);
		bool shouldUpdate(const Jacket& jacket) const;
		void draw(Renderer* renderer, float scrWidth, float scrHeight) const;		
	};

	class ScorePreviewWindow
	{
		Framebuffer previewBuffer;
		ScorePreviewBackground background;
		float scaledAspectRatio;
		std::unique_ptr<Texture> notesTex;

		const Texture& getNoteTexture();
		std::pair<float, float> getNoteBound(const Note& note) const;
		std::pair<float, float> getHoldStepBound(const Note& note, const Score& score) const;
		std::pair<float, float> getHoldSegmentBound(const Note& note, const Score& score, int curTick) const;

		std::array<DirectX::XMFLOAT4, 4> getAuraVPos(const Score& score, const Note& note, int lane, int currentTick, ParticleEffectType type);
		std::array<DirectX::XMFLOAT4, 4> getCircularVPos(const Score& score, const Note& note, int currentTick, ParticleEffectType type);
		std::array<DirectX::XMFLOAT4, 4> getLinearVpos(const Score& score, const Note& note, int lane, float currentTime, float progress, ParticleEffectType type);
		std::array<DirectX::XMFLOAT4, 4> getFlatVPos(const Score& score, const Note& note, int currentTick, ParticleEffectType type);
		std::array<DirectX::XMFLOAT4, 4> getLaneVPos(const Note& note, int lane);
		std::array<DirectX::XMFLOAT4, 4> getSlotVPos(const Note& note, int lane);
		void drawEffectPool(const ScoreContext& context, const std::map<Engine::NoteEffectType, Engine::EffectPool>& effectPoolMap, const Engine::NoteEffectType type, Renderer* renderer);
		
		void drawNoteBase(Renderer* renderer, const Note& note, float left, float right, float y, float zScalar = 1);
		void drawTraceDiamond(Renderer* renderer, const Note& note, float left, float right, float y);
		void drawFlickArrow(Renderer* renderer, const Note& note, float y, double cur_time);
		void drawParticle(Renderer* renderer, const std::array<DirectX::XMFLOAT4, 4>& layout, const Engine::DrawingParticle& particle,
			float progress, const Texture& texture, const Sprite& sprite, int zIndex, Color tint);
		
		void updateToolbar(ScoreEditorTimeline& timeline, ScoreContext& context) const;
		float getScrollbarWidth() const;
		void updateScrollbar(ScoreEditorTimeline& timeline, ScoreContext& context) const;
	public:
		ScorePreviewWindow(); 
		~ScorePreviewWindow();
		void update(ScoreContext& context, Renderer* renderer);
		void updateUI(ScoreEditorTimeline& timeline, ScoreContext& context) const;

		void drawNotes(const ScoreContext& context, Renderer* renderer);
		void drawLines(const ScoreContext& context, Renderer* renderer);
		void drawHoldTicks(const ScoreContext& context, Renderer* renderer);
		void drawHoldCurves(const ScoreContext& context, Renderer* renderer);
		void drawUnderNoteEffects(const ScoreContext& context, Renderer* renderer);
		void drawParticles(const ScoreContext& context, Renderer* renderer);
 		
		void drawStage(Renderer* renderer);
		void drawStageCover(Renderer* renderer);
	};
}