//#include <iostream>
//using namespace std;
//
//class FrameApi {
//public:
//	virtual void draw() = 0;
//protected:
//	FrameApi() {};
//};
//
//class LayoutApi {//�ֱ��ʵĲ�����
//public:
//	virtual void installFrame() = 0;
//protected:
//	LayoutApi() {}
//};
//
////PC�ϵ�Frame
//class ComputerFrame :public FrameApi {
//public:
//	ComputerFrame(int pins) :m_pins(pins) {
//	
//	}
//	void draw() {
//		cout << "pc frame size " << m_pins << endl;
//	}
//private:
//	int m_pins;
//};
//
////mobile�ϵ�Frame
//class MobileFrame :public FrameApi {
//public:
//	MobileFrame(int pins) :m_pins(pins) {
//
//	}
//	void draw() {
//		cout << "mobile frame size " << m_pins << endl;
//	}
//private:
//	int m_pins;
//};
//
////�߷ֱ��ʲ���
//class HighLayout : public LayoutApi {
//public:
//	HighLayout(int frameAdapterPins) :m_FrameAdapterPins(frameAdapterPins) {}
//	void installFrame() {
//		cout << "now in pc, we use high layout " << m_FrameAdapterPins << endl;
//	}
//private:
//	int m_FrameAdapterPins;
//};
//
////�ͷֱ��ʲ���
//class LowLayout : public LayoutApi {
//public:
//	LowLayout(int frameAdapterPins) :m_FrameAdapterPins(frameAdapterPins) {}
//	void installFrame() {
//		cout << "now in mobile, we use low layout " << m_FrameAdapterPins << endl;
//	}
//private:
//	int m_FrameAdapterPins;
//};
//
////������Ʒ�ļ򵥹���
//class FrameFactory {
//public:
//	static FrameApi* createFrame(int type) {
//		switch (type)
//		{
//		case 1:
//			return new ComputerFrame(1024);
//			break;
//		case 2:
//			return new ComputerFrame(480);
//			break;
//		default:
//			break;
//		}
//		return nullptr;
//	}
//};
//
//class LayoutFactory {
//public:
//	static LayoutApi* createLayout(int type) {
//		switch (type)
//		{
//		case 1:
//			return new HighLayout(1024);
//			break;
//		case 2:
//			return new LowLayout(480);
//			break;
//		default:
//			break;
//		}
//		return nullptr;
//	}
//};
//
//class GUIEngineer {
//public:
//	//frameType:����������ѡ��Frame�ؼ�������
//	//layoutType:����������ѡ�񲼾ֹ�����������
//	void prepareDraw(int frameType, int layoutType) {
//		m_frame = FrameFactory::createFrame(frameType);
//		m_layout = LayoutFactory::createLayout(layoutType);
//		m_frame->draw();
//		m_layout->installFrame();
//	}
//private:
//	FrameApi* m_frame;
//	LayoutApi* m_layout;
//};
//
//int main() {
//	GUIEngineer* pEng = new GUIEngineer();
//	pEng->prepareDraw(1, 1);
//
//	system("pause");
//	return 0;
//}