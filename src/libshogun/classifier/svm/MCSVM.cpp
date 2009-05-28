/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2009 Soeren Sonnenburg
 * Written (W) 2009 Marius Kloft
 * Copyright (C) 2009 TU Berlin and Max-Planck-Society
 */

#include "classifier/svm/MCSVM.h"
#include "lib/io.h"

CMCSVM::CMCSVM()
: CMultiClassSVM(TRUE_MULTICLASS), model(NULL)
{
}

CMCSVM::CMCSVM(float64_t C, CKernel* k, CLabels* lab)
: CMultiClassSVM(TRUE_MULTICLASS, C, k, lab), model(NULL)
{
}

CMCSVM::~CMCSVM()
{
	//SG_PRINT("deleting MCSVM\n");
}

bool CMCSVM::train()
{
	struct svm_node* x_space;

	ASSERT(labels && labels->get_num_labels());
	int32_t num_classes = labels->get_num_classes();

	problem.l=labels->get_num_labels();
	SG_INFO( "%d trainlabels\n", problem.l);

	problem.y=new float64_t[problem.l];
	problem.x=new struct svm_node*[problem.l];
	x_space=new struct svm_node[2*problem.l];

	for (int32_t i=0; i<problem.l; i++)
	{
		problem.y[i]=labels->get_label(i);
		problem.x[i]=&x_space[2*i];
		x_space[2*i].index=i;
		x_space[2*i+1].index=-1;
	}

	int32_t weights_label[2]={-1,+1};
	float64_t weights[2]={1.0,get_C2()/get_C1()};

	ASSERT(kernel && kernel->has_features());
    ASSERT(kernel->get_num_vec_lhs()==problem.l);

	param.svm_type=NU_MULTICLASS_SVC; // Nu MC SVM
	param.kernel_type = LINEAR;
	param.degree = 3;
	param.gamma = 0;	// 1/k
	param.coef0 = 0;
	param.nu = get_nu(); // Nu
	param.kernel=kernel;
	param.cache_size = kernel->get_cache_size();
	param.C = 0;
	param.eps = epsilon;
	param.p = 0.1;
	param.shrinking = 0;
	param.nr_weight = 2;
	param.weight_label = weights_label;
	param.weight = weights;
	param.nr_class=num_classes;

	const char* error_msg = svm_check_parameter(&problem,&param);

	if(error_msg)
		SG_ERROR("Error: %s\n",error_msg);

	model = svm_train(&problem, &param);

	if (model)
	{
		ASSERT((model->l==0) || (model->l>0 && model->SV && model->sv_coef && model->sv_coef));

		ASSERT(model->nr_class==num_classes);
		create_multiclass_svm(num_classes);

		for (int32_t i=0; i<num_classes; i++)
		{
			int32_t num_sv=model->nSV[i];

			CSVM* svm=new CSVM(num_sv);
			svm->set_bias(model->rho[i]);

			for (int32_t j=0; j<num_sv; j++)
			{
				svm->set_alpha(j, model->SV[i][j]);
				svm->set_support_vector(j, model->sv_coef[i][j]);
			}

			set_svm(i, svm);
		}

		delete[] problem.x;
		delete[] problem.y;
		delete[] x_space;
		svm_destroy_model(model);

		model=NULL;
		return true;
	}
	else
		return false;
}
