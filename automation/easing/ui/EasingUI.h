class EasingUI :
	public InspectableContentComponent,
	public ContainerAsyncListener
{
public:
	EasingUI(Easing* e);
	virtual ~EasingUI();

	WeakReference<Easing> easing;

	Path drawPath;
	Path hitPath;

	bool showFirstHandle;
	bool showLastHandle;

	int hitPathPrecision = 10;

	Rectangle<float> valueBounds;

	void paint(Graphics& g) override;
	virtual void paintInternal(Graphics&) {}
	void resized() override;

	void generatePath();
	virtual void generatePathInternal();

	void autoGeneratePathWithPrecision(int precision = 50);

	void buildHitPath();

	bool hitTest(int tx, int ty) override;

	virtual void setShowEasingHandles(bool showFirst, bool showLast);

	virtual void newMessage(const ContainerAsyncEvent& e) override;
	virtual void easingControllableFeedbackUpdate(Controllable*) {}

	void setValueBounds(const Rectangle<float> valueBounds);
	Point<int> getUIPosForValuePos(const Point<float>& valuePos) const;
	Point<float> getValuePosForUIPos(const Point<int>& uiPos) const;

	class EasingHandle :
		public Component
	{
	public:
		EasingHandle();
		void paint(Graphics& g) override;
	};
};

class LinearEasingUI :
	public EasingUI
{
public:
	LinearEasingUI(LinearEasing* e);
	void generatePathInternal() override;

	// Inherited via EasingUI
};


class CubicEasingUI :
	public EasingUI
{
public:
	CubicEasingUI(CubicEasing* e);

	CubicEasing* ce;
	EasingHandle h1;
	EasingHandle h2;
	bool syncHandles;

	Point<float> h1ValueAtMouseDown;
	Point<float> h2ValueAtMouseDown;

	bool hitTest(int tx, int ty) override;

	void resized() override;

	void generatePathInternal() override;
	void paintInternal(Graphics& g) override;

	void easingControllableFeedbackUpdate(Controllable*) override;

	void setShowEasingHandles(bool showFirst, bool showLast) override;

	void mouseDown(const MouseEvent& e) override;
	void mouseDrag(const MouseEvent& e) override;
	void mouseUp(const MouseEvent& e) override;
};