#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class ExportHeaderModel {
public:
	ExportHeaderModel(string depId, string exportDate) : m_strDepId(depId), m_strExportDate(exportDate) {
	
	
	}
	string getDepId() const { return m_strDepId; }
	string getExportDate() const { return m_strExportDate; }
private:
	string m_strDepId;//对账单部门ID
	string m_strExportDate;//对账日期
};

class ExportBodyModel {
public:
	ExportBodyModel(string transId, double quintity) : m_strTransId(transId), m_quantity(quintity) {


	}
	string getTransId() const { return m_strTransId; }
	double getQuantity() const { return m_quantity; }
private:
	string m_strTransId;//交易ID
	double m_quantity;//数量
};

class ExportFooterModel {
public:
	ExportFooterModel(string user):m_strUser(user) {
		
	}
	string getUser() { return m_strUser; }
private:
	string m_strUser;//对账人
};

template <class T>
string convertToString(T value) {
	stringstream ss;
	ss << value;
	return ss.str();
}

class Builder {
public:
	virtual void buildHeader(ExportHeaderModel* header) = 0;
	virtual void buildBody(vector<ExportBodyModel*>& body) = 0;
	virtual void buildFooter(ExportFooterModel* footer) = 0;
	virtual string getResult() = 0;
};

class TextBuilder : public Builder {
public:
	virtual void buildHeader(ExportHeaderModel* header) override
	{
		m_strResult.append(header->getDepId() + "|" + header->getExportDate() + "\n");
	}


	virtual void buildBody(vector<ExportBodyModel *>& body) override
	{
		for (auto iter : body)
		{
			m_strResult.append(iter->getTransId() + "|" + convertToString(iter->getQuantity()) + "\n");
		}
	}


	virtual void buildFooter(ExportFooterModel* footer) override
	{
		m_strResult.append(footer->getUser() + "\n");
	}


	virtual string getResult() override
	{
		return m_strResult;
	}

private:
	string m_strResult = "";
};

class XmlBuilder : public Builder {
public:
	virtual void buildHeader(ExportHeaderModel* header) override
	{
		m_strResult.append(header->getDepId() + "|" + header->getExportDate() + ".xml" + "\n");
	}


	virtual void buildBody(vector<ExportBodyModel *>& body) override
	{
		for (auto iter : body)
		{
			m_strResult.append(iter->getTransId() + "|" + convertToString(iter->getQuantity()) + ".xml" + "\n");
		}
	}


	virtual void buildFooter(ExportFooterModel* footer) override
	{
		m_strResult.append(footer->getUser() + ".xml" + "\n");
	}


	virtual string getResult() override
	{
		return m_strResult;
	}

private:
	string m_strResult = "";
};

class Director {
public:
	Director(Builder* builder) {
		m_builder = builder;
	}

	void contruct(ExportHeaderModel* header, vector<ExportBodyModel*>& body, ExportFooterModel* footer) {
		m_builder->buildHeader(header);
		m_builder->buildBody(body);
		m_builder->buildFooter(footer);
	}
private:
	Builder* m_builder;
};

class ExportDataToTxtHelper {
public:
	void doExport(ExportHeaderModel* pHead, vector<ExportBodyModel*>& pVecBody, ExportFooterModel* pFooter) {
		string result;
		result += pHead->getDepId() + "|"+ pHead->getExportDate() + "\n";
		
		for (auto iter: pVecBody)
		{
			result += iter->getTransId() + "|" + convertToString(iter->getQuantity()) + "\n";
		}
		
		result += pFooter->getUser() + "\n";
		
		cout << result;
	}
};

class ExportDataToXmlHelper {
public:
	void doExport(ExportHeaderModel* pHead, vector<ExportBodyModel*>& pVecBody, ExportFooterModel* pFooter) {
		string result;
		result += pHead->getDepId() + "|" + pHead->getExportDate() + ".xml" + "\n";

		for (auto iter : pVecBody)
		{
			result += iter->getTransId() + "|" + convertToString(iter->getQuantity()) + ".xml" + "\n";
		}

		result += pFooter->getUser() + "\n" + ".xml";

		cout << result;
	}
};

int main() {
	ExportHeaderModel* pHead = new ExportHeaderModel("信用社", "5月10日");
	ExportBodyModel* pBody1 = new ExportBodyModel("1111", 10000.00f);
	ExportBodyModel* pBody2 = new ExportBodyModel("1112", 20000.00f);
	vector<ExportBodyModel*> vecBody;
	vecBody.push_back(pBody1);
	vecBody.push_back(pBody2);
	ExportFooterModel* pFooter = new ExportFooterModel("bo");
	//(new ExportDataToTxtHelper())->doExport(pHead, vecBody, pFooter);
	Builder* builer = new XmlBuilder();
	Director* director = new Director(builer);
	director->contruct(pHead, vecBody, pFooter);
	cout << builer->getResult() << endl;
	system("pause");
	return 0;
}