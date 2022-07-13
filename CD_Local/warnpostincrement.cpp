#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/FileManager.h"
#include "clang/Frontend/CompilerInstance.h"
#include "llvm/Support/raw_ostream.h"
#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/AST/AST.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Sema/Sema.h"
#include "clang/AST/Decl.h"
#include<iostream>

using namespace clang;

class WarnPostIncrementVisitor : public RecursiveASTVisitor<WarnPostIncrementVisitor> {
	private:
		ASTContext *context;
		CompilerInstance& instance;

		DiagnosticsEngine& d;

		unsigned int warningID;

			bool isInHeader(Decl *decl) {
			auto loc = decl->getLocation();
			auto floc = context->getFullLoc(loc);
			if (floc.isInSystemHeader()) return true;
			auto entry = floc.getFileEntry()->getName();
			return false;
		}

		void checkName(std::string name, Decl *decl) {
			int n = name.length();
			std::cout<<name<<std::endl;
			if(name.at(n-1)=='+' and name.at(n-2)=='+'){
				auto loc = context->getFullLoc(decl->getLocation());
				d.Report(loc, warningID) << name;
			}
		}


	public:
		WarnPostIncrementVisitor(ASTContext *context, CompilerInstance& instance): context(context), instance(instance), d(instance.getDiagnostics()) {
			warningID = d.getCustomDiagID(DiagnosticsEngine::Warning, "Post Increment was used: '%0'");
		}
		virtual bool VisitFunctionDecl(FunctionDecl *d) {
			if (isInHeader(d)) {
				return true;
			}
			checkName(d->getNameAsString(), d);
			return true;
		}

		virtual bool VisitVarDecl(VarDecl *d) {
			if (isInHeader(d)) {
				return true;
			}
			isLocalVarDecl(d);
			checkName(d->getNameAsString(), d);
			return true;
		}


};

class WarnPostIncrementConsumer : public ASTConsumer {
	CompilerInstance& instance;
	WarnPostIncrementVisitor visitor;

	public:
	WarnPostIncrementConsumer(CompilerInstance &instance)
			: instance(instance), visitor(&instance.getASTContext(), instance) {}

	virtual void HandleTranslationUnit(ASTContext &context) override {
		visitor.TraverseDecl(context.getTranslationUnitDecl());
	}

};

class WarnPostIncrementAction : public PluginASTAction {
protected:
	virtual std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance& instance, llvm::StringRef) override {
		return std::make_unique<WarnPostIncrementConsumer>(instance);
	}

	virtual bool ParseArgs(const CompilerInstance&, const std::vector<std::string>&) override {
		return true;
	}

	virtual PluginASTAction::ActionType getActionType() override {
  		return PluginASTAction::AddAfterMainAction;
	}
};

static FrontendPluginRegistry::Add<WarnPostIncrementAction> WarnPostIncrement("WarnPostIncrement", "Warn against post increment operator for non-primitive data types");

