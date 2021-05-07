.. ltr++ documentation master file, created by
   sphinx-quickstart on Sun Feb 28 22:42:34 2021.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to ltr++'s documentation!
=====================================

Learning to Rank (LTR) is one of the methods that can be effectively applied to solve the task
of creating a ranking model in Information Retrieval. It helps solving IR problems such as document retrieval,
collaborative filtering, sentiment analysis, computational advertising etc. LTR method aims at learning a model
that given a query and a set of candidate documents finds the appropriate ranking of documents according to their relevancy.
LTR method aims at learning a model that given a query and a set of candidate documents finds the appropriate ranking
of documents according to their relevancy.
**LTR++** is a Learning to Rank open-source library based on `RankLib`_ project. Currently two popular algorithms have been implemented
and it also implements many retrieval metrics. 

.. image:: ./img/ltr_flow.png
  :width: 800
  :alt: Simple Learning to Rank workflow diagram.

.. _RankLib: https://sourceforge.net/p/lemur/wiki/RankLib/

The LTR++ project is in early steps of development. Feel free to contribute or suggest features!

.. toctree::
   :maxdepth: 2
   :caption: Contents:

   quickstart
   integration
   components
   license
   help


